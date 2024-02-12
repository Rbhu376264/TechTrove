#include "mm.h"        // prototypes of functions implemented in this file
#include "mm_list.h"   // "mm_list_..."  functions -- to manage explicit free list
#include "mm_block.h"  // "mm_block_..." functions -- to manage blocks on the heap
#include "memlib.h"    // mem_sbrk -- to extend the heap
#include <string.h>    // memcpy -- to copy regions of memory

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

/**
 * Mark a block as free, coalesce with contiguous free blocks on the heap, add
 * the coalesced block to the free list.
 *
 * @param bp address of the block to mark as free
 * @return the address of the coalesced block
 */
static BlockHeader *free_coalesce(BlockHeader *bp) {

    // mark block as free
    int size = mm_block_size(bp);
    mm_block_set_header(bp, size, 0);
    mm_block_set_footer(bp, size, 0);

    // check whether contiguous blocks are allocated
    int prev_alloc = mm_block_allocated(mm_block_prev(bp));
    int next_alloc = mm_block_allocated(mm_block_next(bp));
    //Check for threshold
    if (prev_alloc && next_alloc) {
        // TODO: add bp to free list
        // if(size >= 512)
        // {
        //     mm_list_append(bp);
        // }
        // else{
        //     mm_list_prepend(bp);
        // }
        mm_list_append(bp);
        return bp;

    } else if (prev_alloc && !next_alloc) {
        // TODO: remove next block from free list
        // TODO: add bp to free list
        // TODO: coalesce with next block
        BlockHeader* next = mm_block_next(bp);
        mm_list_remove(next);
        // if(size >= 512)
        // {
        //     mm_list_append(bp);
        // }
        // else{
        //     mm_list_prepend(bp);
        // }
        mm_list_append(bp);
        int curr_sz = size + mm_block_size(next);
        mm_block_set_header(bp, curr_sz, 0);
        mm_block_set_footer(bp, curr_sz, 0);

        return bp;

    } else if (!prev_alloc && next_alloc) {
        // TODO: coalesce with previous block
        
        BlockHeader* prev = mm_block_prev(bp);
        int curr_sz = size + mm_block_size(prev);
        mm_block_set_header(prev, curr_sz, 0);
        mm_block_set_footer(prev, curr_sz, 0);

        return prev;

    } else {
        // TODO: remove next block from free list
        // TODO: coalesce with previous and next block

        BlockHeader* prev = mm_block_prev(bp);
        int curr_sz = size + mm_block_size(mm_block_prev(bp)) + mm_block_size(mm_block_next(bp));
        mm_list_remove(mm_block_next(bp));
        mm_block_set_header(prev, curr_sz, 0);
        mm_block_set_footer(prev, curr_sz, 0);

        return prev;
    }
}

/**
 * Allocate a free block of `size` byte (multiple of 8) on the heap.
 *
 * @param size number of bytes to allocate (a multiple of 8)
 * @return pointer to the header of the allocated block
 */
static BlockHeader *extend_heap(int size) {

    // bp points to the beginning of the new block
    char *bp = mem_sbrk(size);
    if ((long)bp == -1)
        return NULL;

    // write header over old epilogue, then the footer
    BlockHeader *old_epilogue = (BlockHeader *)bp - 1;
    mm_block_set_header(old_epilogue, size, 0);
    mm_block_set_footer(old_epilogue, size, 0);

    // write new epilogue
    mm_block_set_header(mm_block_next(old_epilogue), 0, 1);

    // merge new block with previous one if possible
    return free_coalesce(old_epilogue);
}

int mm_init(void) {

    // init list of free blocks
    mm_list_init();

    // create empty heap of 4 x 4-byte words
    char *new_region = mem_sbrk(16);
    if ((long)new_region == -1)
        return -1;

    heap_blocks = (BlockHeader *)new_region;
    mm_block_set_header(heap_blocks, 0, 0);      // skip 4 bytes for alignment
    mm_block_set_header(heap_blocks + 1, 8, 1);  // allocate a block of 8 bytes as prologue
    mm_block_set_footer(heap_blocks + 1, 8, 1);
    mm_block_set_header(heap_blocks + 3, 0, 1);  // epilogue (size 0, allocated)
    heap_blocks += 1;                            // point to the prologue header

    // TODO: extend heap with an initial heap size
    extend_heap(1024);

    return 0;
}

void mm_free(void *bp) {
    // TODO: move back 4 bytes to find the block header, then free block
    BlockHeader *ptr = (BlockHeader *) bp - 1;
    free_coalesce(ptr);
}

/**
 * Find a free block with size greater or equal to `size`.
 *
 * @param size minimum size of the free block
 * @return pointer to the header of a free block or `NULL` if free blocks are
 *         all smaller than `size`.
 */
static BlockHeader *find_fit(int size) {
    // TODO: implement
    BlockHeader *curr = mm_list_headp;
    while(curr != NULL)
    {   
        if(mm_block_size(curr) >= size)
        {
            return curr;
        }

        curr = mm_list_next(curr);
    }
    return NULL;
}

/**
 * Allocate a block of `size` bytes inside the given free block `bp`.
 *
 * @param bp pointer to the header of a free block of at least `size` bytes
 * @param size bytes to assign as an allocated block (multiple of 8)
 * @return pointer to the header of the allocated block
 */
static BlockHeader *place(BlockHeader *bp, int size) {
    // TODO: if current size is greater, use part and add rest to free list
    // TODO: return pointer to header of allocated block
    // if(mm_block_size(bp) - size >= 16)
    if(mm_block_size(bp) - size >= 16)
    {
        if(size >= 100)
        {
            //printf("Case1\n");
            mm_list_remove(bp);
            int remaining_sz = mm_block_size(bp) - size;
            mm_block_set_header(bp,size,1);
            mm_block_set_footer(bp,size,1);
            
            BlockHeader *addr_sz = mm_block_next(bp); 
            mm_block_set_header(addr_sz,remaining_sz,0);
            mm_block_set_footer(addr_sz,remaining_sz,0);
            // if(mm_block_size(addr_sz) >= 512){
            //     mm_list_append(addr_sz);
            // }
            // else{
            //     mm_list_prepend(addr_sz);
            // }
            mm_list_append(addr_sz);
            return bp;
        }
        else
        {
            mm_list_remove(bp);
            int remaining_sz = mm_block_size(bp) - size;
            
            
            mm_block_set_header(bp,remaining_sz,0);
            mm_block_set_footer(bp,remaining_sz,0);
            
            BlockHeader *addr_sz = mm_block_next(bp); 
            
            mm_block_set_header(addr_sz,size,1);
            mm_block_set_footer(addr_sz,size,1);
            // if(mm_block_size(bp)>=512)
            // {
            //     mm_list_append(bp);
            // }
            // else{
            //     mm_list_prepend(bp);
            // }
            mm_list_append(bp);

            return addr_sz;

        }
        
        //free_coalesce(addr_sz);
        
    }
    else
    {
        ////printf("Case 3\n");
        mm_block_set_header(bp,mm_block_size(bp),1);
        mm_block_set_footer(bp,mm_block_size(bp),1);

        mm_list_remove(bp);

        return bp;
    }
    return NULL;
}

/**
 * Compute the required block size (including space for header/footer) from the
 * requested payload size.
 *
 * @param payload_size requested payload size
 * @return a block size including header/footer that is a multiple of 8
 */
static int required_block_size(int payload_size) {
    payload_size += 8;                    // add 8 for for header/footer
    return ((payload_size + 7) / 8) * 8;  // round up to multiple of 8
}

void *mm_malloc(size_t size) {
    // ignore spurious requests
    if (size == 0)
        return NULL;

    int required_size = required_block_size(size);

    // TODO: find a free block or extend heap
    // TODO: allocate and return pointer to payload
    BlockHeader *blocky = find_fit(required_size);
    if(blocky != NULL)
    {
        return mm_block_payload_addr(place(blocky, required_size));
    }
    else{

        extend_heap(MAX(1024,required_size));

        BlockHeader* hd = find_fit(required_size);

        return mm_block_payload_addr(place(hd,required_size));

    }
    return NULL;
}

void *mm_realloc(void *ptr, size_t size) {

    if (ptr == NULL) {
        // equivalent to malloc
        return mm_malloc(size);

    } else if (size == 0) {
        // equivalent to free
        mm_free(ptr);
        return NULL;

    } else {
        // TODO: reallocate, reusing current block if possible
        // TODO: copy data over new block with memcpy
        // TODO: return pointer to payload of new block
        int curr_size = mm_block_size(ptr-4);
        size = required_block_size(size);
        BlockHeader* bptr = (BlockHeader *) (ptr-4);
        
        //size <= curr_size then return ptr
        //next block is free then should check size > curr_size, if curr_sz + next_sz - size >=16 then make block of curr_sz + next_sz then you split else combing the current and next block.
        if((int)size <= curr_size){
            return ptr;
        }
        if(!mm_block_allocated(mm_block_next(ptr-4))){
            int comb_sz = mm_block_size(ptr-4) + mm_block_size(mm_block_next(ptr-4));

            if(comb_sz >= (int)size){
                mm_list_remove(mm_block_next(bptr));

                mm_block_set_header(bptr,comb_sz, 1);
                mm_block_set_footer(bptr,comb_sz, 1);
                

                return mm_block_payload_addr(bptr);

            }

        }
        if(!mm_block_allocated(mm_block_prev(ptr-4))){
            int comb_sz = mm_block_size(ptr-4) + mm_block_size(mm_block_prev(ptr-4));
            BlockHeader* prev = mm_block_prev(bptr);

            if(comb_sz >= (int)size){
                mm_list_remove(prev);

                memmove(mm_block_payload_addr(prev),ptr,(unsigned)mm_block_size(ptr-4)-8);
                mm_block_set_header(prev,comb_sz, 1);
                mm_block_set_footer(prev,comb_sz, 1);

                return mm_block_payload_addr(prev);
            }


            
        }

        // TODO: remove this naive implementation
        void *new_ptr = mm_malloc(size);
        memcpy(new_ptr, ptr, MIN(size, (unsigned)mm_block_size(ptr-4) - 8));
        mm_free(ptr);
        return new_ptr;
    }
}
