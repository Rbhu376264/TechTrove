#include <getopt.h>  // getopt, optarg
#include <stdlib.h>  // exit, atoi, malloc, free
#include <stdio.h>   // printf, fprintf, stderr, fopen, fclose, FILE
#include <limits.h>  // ULONG_MAX
#include <string.h>  // strcmp, strerror
#include <errno.h>   // errno

/* fast base-2 integer logarithm */
#define INT_LOG2(x) (31 - __builtin_clz(x))
#define NOT_POWER2(x) (__builtin_clz(x) + __builtin_ctz(x) != 31)

/* tag_bits = ADDRESS_LENGTH - set_bits - block_bits */
#define ADDRESS_LENGTH 64

/**
 * Print program usage (no need to modify).
 */
static void print_usage() {
    printf("Usage: csim [-hv] -S <num> -K <num> -B <num> -p <policy> -t <file>\n");
    printf("Options:\n");
    printf("  -h           Print this help message.\n");
    printf("  -v           Optional verbose flag.\n");
    printf("  -S <num>     Number of sets.           (must be > 0)\n");
    printf("  -K <num>     Number of lines per set.  (must be > 0)\n");
    printf("  -B <num>     Number of bytes per line. (must be > 0)\n");
    printf("  -p <policy>  Eviction policy. (one of 'FIFO', 'LRU')\n");
    printf("  -t <file>    Trace file.\n\n");
    printf("Examples:\n");
    printf("$ ./csim    -S 16  -K 1 -B 16 -p LRU -t traces/yi2.trace\n");
    printf("$ ./csim -v -S 256 -K 2 -B 16 -p LRU -t traces/yi2.trace\n");
}

/* Parameters set by command-line args (no need to modify) */
int verbose = 0;   // print trace if 1
int S = 0;         // number of sets
int K = 0;         // lines per set
int B = 0;         // bytes per line

typedef enum { FIFO = 1, LRU = 2 } Policy;
Policy policy;     // 0 (undefined) by default

FILE *trace_fp = NULL;

/**
 * Parse input arguments and set verbose, S, K, B, policy, trace_fp.
 *
 * TODO: Finish implementation
 */
static void parse_arguments(int argc, char **argv) {
    char c;
    while ((c = getopt(argc, argv, "S:K:B:p:t:vh")) != -1) {
        switch(c) {
            case 'S':
                S = atoi(optarg);
                if (NOT_POWER2(S)) {
                    fprintf(stderr, "ERROR: S must be a power of 2\n");
                    exit(1);
                }
                break;
            case 'K':
                // TODO
                K = atoi(optarg); //Its used to parse in the K.
                break;
            case 'B':
                // TODO
                B = atoi(optarg); //Its used to parse in B and then check if it is power of 2 or not.
                if (NOT_POWER2(B)) {
                    fprintf(stderr, "ERROR: B must be a power of 2\n");
                    exit(1);
                }
                break;
            case 'p':
                if (!strcmp(optarg, "FIFO")) { //This checks for policies whether its FIFO or LRU.
                    policy = FIFO;
                } else if(!strcmp(optarg, "LRU")){
                    policy = LRU;
                }else{
                    fprintf(stderr, "ERROR: p must be either FIFO or LRU \n");
                    exit(1);
                }
                // TODO: parse LRU, exit with error for unknown policy
                break;
            case 't':
                // TODO: open file trace_fp for reading
                trace_fp = fopen(optarg,"r"); //It checks for the trace file as an input.
                if (!trace_fp) {
                    fprintf(stderr, "ERROR: %s: %s\n", optarg, strerror(errno));
                    exit(1);
                }
                break;
            case 'v':
                // TODO
                verbose = 1; //If verbose is passed in it is passed as v.
                break;
            case 'h':
                // TODO
                print_usage(); //If h is passed this function will execute.
                exit(0);
            default:
                print_usage();
                exit(1);
        }
    }

    /* Make sure that all required command line args were specified and valid */
    if (S <= 0 || K <= 0 || B <= 0 || policy == 0 || !trace_fp) {
        printf("ERROR: Negative or missing command line arguments\n");
        print_usage();
        if (trace_fp) {
            fclose(trace_fp);
        }
        exit(1);
    }

    /* Other setup if needed */



}

/**
 * Cache data structures
 * TODO: Define your own!
 */
 //The struct below consists of valid bit, tag, offset and a track(to keep track of the entries as when they inserted or removed)
struct Line{   
    int valid_bit;
    int tag;
    int offset;
    int track;

};

struct Line **cache;
int counter = 0; // Global counter to assign various track values to elements inserted and removed from cache.


/**
 * Allocate cache data structures.
 *
 * This function dynamically allocates (with malloc) data structures for each of
 * the `S` sets and `K` lines per set.
 *
 * TODO: Implement
 */
static void allocate_cache() {

    cache = (struct Line **)malloc(S* sizeof(struct Line*)); //Cache is allocated of size of S * size of lines, to have that many sets.
    for (int i = 0; i < S;  i = i+1){
        cache[i] = malloc(K * sizeof(struct Line)); //Each cache set has these many lines, then we initialze these parameters..
        for(int j = 0; j < K; j = j + 1){
            cache[i][j].valid_bit = 0;
            cache[i][j].tag = 0;
            cache[i][j].offset = 0;
            cache[i][j].track = 0;
        }
        
    }

}

/**
 * Deallocate cache data structures.
 *
 * This function deallocates (with free) the cache data structures of each
 * set and line.
 *
 * TODO: Implement
 */
static void free_cache() {

    for (int i = 0; i < S; i = i+1){ 
         free(cache[i]);

   }

    free(cache);



}

/* Counters used to record cache statistics */
int miss_count     = 0;
int hit_count      = 0;
int eviction_count = 0;

/**
 * Simulate a memory access.
 *
 * If the line is already in the cache, increase `hit_count`; otherwise,
 * increase `miss_count`; increase `eviction_count` if another line must be
 * evicted. This function also updates the metadata used to implement eviction
 * policies (LRU, FIFO).
 *
 * TODO: Implement
 */
static void access_data(unsigned long addr) {
    // printf("Access to %016lx\n", addr);

    int b = INT_LOG2(B); //the block offset is taken from here.
    int s = INT_LOG2(S); //the set bits are calculated from here.
    int set_and_offset = addr & ((1<<(s+b)) - 1); //Here I first extracted set and the offset from the address.
    int extracting_set = (set_and_offset &  ~((1<<b) - 1)) >> b; //Then I extracted the set from the address.
    int tag_bits = (addr)>>(s+b); //Finally I got tag out of the address.

    for(int i = 0; i<K; i++) //Helps in getting us the hit in cache.
    {
        if(cache[extracting_set][i].valid_bit == 1 && cache[extracting_set][i].tag == tag_bits){
            hit_count++;
            
            if(policy == 2){
                cache[extracting_set][i].track = counter;
            }
            counter++;
            return;
        }
    }

    miss_count++;

    for(int i = 0; i<K; i++) //Helps in getting the miss in the cache.
    {
        if(cache[extracting_set][i].valid_bit == 0){
            cache[extracting_set][i].valid_bit = 1;
            cache[extracting_set][i].tag = tag_bits;
            cache[extracting_set][i].track = counter;
            counter++;
            return;
        }
    }
        
    eviction_count++;

    int idx = 0;
    int evict = INT_MAX;
    for(int i = 0; i<K; i++){ //Finds the smallest track number element and removes it from the cache.

        if(cache[extracting_set][i].track < evict)
        {
            idx = i;
            evict = cache[extracting_set][i].track;
        }

    }
    cache[extracting_set][idx].tag = tag_bits;
    cache[extracting_set][idx].track = counter;
    counter++;
    

}

/**
 * Replay the input trace.
 *
 * This function:
 * - reads lines (e.g., using fgets) from the file handle `trace_fp` (a global variable)
 * - skips lines not starting with ` S`, ` L` or ` M`
 * - parses the memory address (unsigned long, in hex) and len (unsigned int, in decimal)
 *   from each input line
 * - calls `access_data(address)` for each access to a cache line
 *
 * TODO: Implement
 */
static void replay_trace() {
    
    char buff[100]; //Buffer of size 100.
    char str[1]; //Used to store instruction value be it I, M, S, L.
    unsigned long addry; //Used to store address.
    int byte_access; // Used to store number of bytes.
    while(fgets(buff, 20, trace_fp) != NULL)
    {
       
        sscanf( buff , "%s %lx,%d", str, &addry, &byte_access); //Scanner used to parse in the values.
        
        if(!strcmp(str, "M")){    //Checks whether the instruction is M, then we access the data twice.
            
            for(int i = 0; i<2; i++){
                
                int numy = addry % B;
                if(numy + byte_access > B){
                    for(int i = 0; i<byte_access + numy; i+=B){
                        access_data(addry + i);
                    }
                }else{
                    access_data(addry);
                }
            }

        }else if(!strcmp(str, "I")){ //If instruction is I then we continue
            continue;

        }
        else{ //In case of S and L we just run on this snippet of code, also having cases here is to only access bytes within offset.
            int numy = addry % B;
            if(numy + byte_access > B){
                for(int i = 0; i<byte_access + numy; i+=B){
                    access_data(addry + i);
                }
            }else{
                access_data(addry);
            }

        }


    }


}

/**
 * Print cache statistics (DO NOT MODIFY).
 */
static void print_summary(int hits, int misses, int evictions) {
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
}

int main(int argc, char **argv) {
    parse_arguments(argc, argv);  // set global variables used by simulation
    allocate_cache();             // allocate data structures of cache
    replay_trace();               // simulate the trace and update counts
    free_cache();                 // deallocate data structures of cache
    fclose(trace_fp);             // close trace file
    print_summary(hit_count, miss_count, eviction_count);  // print counts
    return 0;
}
