#ifndef HT_H
#define HT_H
#include <vector>
#include <iostream>
#include <cmath>

typedef size_t HASH_INDEX_T;


// Complete - Base Prober class
struct Prober {
    // Data members
    HASH_INDEX_T start_;     // initial hash location, h(k)
    HASH_INDEX_T m_;         // table size
    HASH_INDEX_T numProbes_; // probe attempts for statistic tracking
    static const HASH_INDEX_T npos = (HASH_INDEX_T)-1; // used to indicate probing failed
    void init(HASH_INDEX_T start, HASH_INDEX_T m) 
    {
        start_ = start;
        m_ = m;
        numProbes_ = 0;
    }
    HASH_INDEX_T next() {
        throw std::logic_error("Not implemented...should use derived class");
    }
};

// Almost Complete - Fill in the if statement below.
struct LinearProber : public Prober {

    HASH_INDEX_T next() 
    {
        // Complete the condition below that indicates failure
        // to find the key or an empty slot
        if(numProbes_ == m_) {
            return npos; 
        }
        HASH_INDEX_T loc = (start_ + numProbes_) % m_;
        numProbes_++;
        return loc;
    }
};

// To be completed
struct QuadraticProber : public Prober {
    HASH_INDEX_T next() 
    {
        // In quadratic probing with a prime table size,
        //  only m/2 probes are guaranteed before revisiting a 
        //  location (and potential cycle of locations)
        if(numProbes_ > m_/2 && numProbes_ <= m_) {
            return npos; 
        }
        // Add code here
        HASH_INDEX_T loc = (start_ + (HASH_INDEX_T)pow(numProbes_,2)) % m_;
        numProbes_++;
        return loc;


    }
};


// Hash Table Interface
template<
    typename K, 
    typename V, 
    typename Prober = LinearProber,
    typename Hash = std::hash<K>, 
    typename KEqual = std::equal_to<K> >
class HashTable
{
public:
    typedef K KeyType;
    typedef V ValueType;
    typedef std::pair<KeyType, ValueType> ItemType;
    typedef Hash Hasher;
    struct HashItem {
        ItemType item;
        bool deleted;
        HashItem(const ItemType& newItem){
            item = newItem;
            deleted = false;
        }
    };

    /**
     * @brief Construct a new Hash Table object
     * 
     * @param resizeAlpha Loading factor threshold at which the table should resize
     * @param prober Probing object of type Prober
     * @param hash Hash functor that supports hash(key) and returns a HASH_INDEX_T
     * @param kequal Functor that checks equality of two KeyType objects
     */
    HashTable(
        double resizeAlpha = 0.4, 
        const Prober& prober = Prober(),
        const Hasher& hash = Hasher(), 
        const KEqual& kequal = KEqual());

    /**
     * @brief Destroy the Hash Table object and delete all remaining
     *         key,value pairs
     * 
     */
    ~HashTable();

    /**
     * @brief Returns true if the table has no non-deleted key,value pairs,
     *        and false otherwise
     * 
     */
    bool empty() const;

    /**
     * @brief Returns number of (non-deleted) key,value pairs in the table
     * 
     * @return size_t 
     */
    size_t size() const;

    /**
     * @brief Inserts a new item into the map, or, if an item with the
     *        given key already exists, it updates the Value of that item
     *        with the second value of the pair, p
     * 
     * @param p Pair to insert  
     * @throw std::logic_error If no free location can be found
     */
    void insert(const ItemType& p);

    /**
     * @brief Removes (marks as deleted) the item with the given key.  
     * Does nothing if an item with the given key does not exist.
     * 
     * @param key 
     */
    void remove(const KeyType& key);

    /**
     * @brief Finds an item with the given key and returns a pointer 
     * to the key,value pair
     * 
     * @param key 
     * @return ItemType const* nullptr is returned if the key does not exist
     */
    ItemType const * find(const KeyType& key) const;
    ItemType * find(const KeyType& key);

    /**
     * @brief Returns the value corresponding to the given key
     * 
     * @param key 
     * throw std::out_of_range if the key does not exist
     * @return ValueType Value associated with key
     */
    const ValueType& at(const KeyType& key) const;
    ValueType& at(const KeyType& key);
    const ValueType& operator[](const KeyType& key) const;
    ValueType& operator[](const KeyType& key);

    // Debug / Performance functions
    void reportAll(std::ostream& out) const;
    void clearTotalProbes() { totalProbes_ = 0; }
    size_t totalProbes() const { return totalProbes_; }
private:
    /**
     * @brief Helper routine to find a given key
     * 
     * @param key 
     * @return HashItem* returns nullptr if key does not exist
     */
    HashItem * internalFind(const KeyType& key) const;
    /**
     * @brief Performs the probing sequence and returns the index
     * of the table location with the given key or the location where
     * key can be inserted (i.e. the index now contains nullptr) but is
     * available.
     * 
     * @param key 
     * @return returns npos is the key does not exist and
     * no free location is available
     */
    HASH_INDEX_T probe(const KeyType& key) const;

    // Constant to signify an invalid hash location is being returned
    static const HASH_INDEX_T npos = Prober::npos;

    /**
     * @brief Resizes the hash table replacing the old with a new
     * table of the next prime size given in CAPACITIES.  Must rehash
     * all non-deleted items while freeing all deleted items.
     * 
     * Must run in O(m) where m is the new table size
     * 
     * @throws std::logic_error if no more CAPACITIES exist
     */
    void resize();

    // Data members
    std::vector<HashItem*> table_; // actual hash table
    Hasher hash_;   
    KEqual kequal_;
    mutable Prober prober_;  // mutable allows const member functions to modify this member
    // debug/performance counters
    mutable size_t totalProbes_; // mutable allows const member functions to modify this member
    // prime capacities to be used when resizing/rehashing is needed
    static const HASH_INDEX_T CAPACITIES[];
    HASH_INDEX_T mIndex_;  // index to CAPACITIES

    // ADD MORE DATA MEMBERS HERE, AS NECESSARY
    HASH_INDEX_T table_size;
    size_t size_ = 0;
    size_t numDelete = 0;
    double rAlpha_;

};

// ----------------------------------------------------------------------------
//                           Hash Table Implementation
// ----------------------------------------------------------------------------

// Static array of prime table sizes
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
const HASH_INDEX_T HashTable<K,V,Prober,Hash,KEqual>::CAPACITIES[] =
    {
        11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877,
        205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969,
        105359969, 210719881, 421439783, 842879579, 1685759167
    };

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HashTable<K,V,Prober,Hash,KEqual>::HashTable(
    double resizeAlpha, const Prober& prober, const Hasher& hash, const KEqual& kequal)
       :  hash_(hash), kequal_(kequal), prober_(prober), rAlpha_(resizeAlpha)
{
    mIndex_ = 0;
    totalProbes_ = 0;
    // Initialize any other data members as necessary
    table_size = CAPACITIES[mIndex_];

    table_.resize(table_size);

    for(unsigned int i = 0; i<table_.size(); i++)
    {
        table_[i] = nullptr;
    }

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HashTable<K,V,Prober,Hash,KEqual>::~HashTable()
{
    for(unsigned int i = 0; i<table_.size(); i++)
    {
        delete table_[i];
    }


}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
bool HashTable<K,V,Prober,Hash,KEqual>::empty() const
{
    for(unsigned int i = 0; i<table_size; i++)
    {
        if(table_[i] != nullptr)
        {
            if(table_[i]->deleted != true)
            {
                return false;
            }
        }
    }

    return true;

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
size_t HashTable<K,V,Prober,Hash,KEqual>::size() const
{
    
    return size_;

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::insert(const ItemType& p)
{  
    
    // std::cout<<"Line 309"<<table_size<<std::endl;
    if(((double)(size_+numDelete)/table_size)>=rAlpha_)
    {
        // std::cout<<"Line 308 "<<((double)(size_+numDelete)/table_size)<<std::endl;
        resize();
    }  
    HASH_INDEX_T spot = this->probe(p.first);
    // std::cout<<"line 289 "<<spot<<std::endl;
    if(spot == npos)
    {
        throw std::logic_error("No free location found");
    }
    // ItemType* place = find(p.first);
    
      
    if(table_[spot] == nullptr)
    {
        HashItem* x = new HashItem(p);
        // HASH_INDEX_T spot = this->probe(p.first);
        // std::cout<<"LIne 306"<<spot<<std::endl;
        table_[spot] = x;
        size_++;
        // std::cout<<"line 302 "<<size_<<std::endl;
    }
    else
    {
        table_[spot]->item.second = p.second;

        if(table_[spot]->deleted == true)
        {
            table_[spot]->deleted = false;
        }
    }
    

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::remove(const KeyType& key)
{
    HashItem* itm_to_delete = internalFind(key);
    if(itm_to_delete != nullptr)
    {
        itm_to_delete->deleted = true;
        size_--;
        numDelete++;
    }

}


// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ItemType const * HashTable<K,V,Prober,Hash,KEqual>::find(const KeyType& key) const
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return &table_[h]->item;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ItemType * HashTable<K,V,Prober,Hash,KEqual>::find(const KeyType& key)
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return &table_[h]->item;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
const typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& HashTable<K,V,Prober,Hash,KEqual>::at(const KeyType& key) const
{
    HashItem const * item = this->internalFind(key);
    if(item == nullptr) { throw std::out_of_range("Bad key"); }
    return item->item.second;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& HashTable<K,V,Prober,Hash,KEqual>::at(const KeyType& key)
{
    HashItem * item = this->internalFind(key);
    if(item == nullptr) { throw std::out_of_range("Bad key"); }
    return item->item.second;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
const typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& HashTable<K,V,Prober,Hash,KEqual>::operator[](const KeyType& key) const
{
    return this->at(key);
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& HashTable<K,V,Prober,Hash,KEqual>::operator[](const KeyType& key)
{
    return this->at(key);
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::HashItem* HashTable<K,V,Prober,Hash,KEqual>::internalFind(const KeyType& key) const
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return table_[h];
}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::resize()
{
    if( mIndex_ == sizeof(CAPACITIES)/sizeof(CAPACITIES[0])-1)
    {
        throw std::logic_error("Cannot resize further");
    }

    // Add your resize code below
    std::vector<HashItem*> table_new;
    std::vector<HashItem*> table_old = table_;
    table_new.resize(CAPACITIES[++mIndex_]);

    for(unsigned int i = 0; i<table_new.size(); i++)
    {
        table_new[i] = nullptr;
    }

    table_ = table_new;
    table_size = table_new.size();
    // std::cout<<"line 409"<<std::endl;
    size_ = 0;
    for(unsigned int i = 0; i<table_old.size(); i++)
    {
        
        if(table_old[i] != nullptr)
        {
            // std::cout<<table_old[i]->item.first<<std::endl;
            if(table_old[i]->deleted == false)
            {
                HASH_INDEX_T spot = this->probe(table_old[i]->item.first);
                table_[spot] = table_old[i];
                size_++;

            }
            else if(table_old[i]->deleted == true)
            {
                delete table_old[i];
                numDelete--;
            }
        }
    }




    
}

// Almost complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HASH_INDEX_T HashTable<K,V,Prober,Hash,KEqual>::probe(const KeyType& key) const
{
    HASH_INDEX_T h = hash_(key) % CAPACITIES[mIndex_];

    prober_.init(h, CAPACITIES[mIndex_]);

    HASH_INDEX_T loc = prober_.next(); 
    totalProbes_++;
    // std::cout<<"line 438 "<<loc<<std::endl;
    while(Prober::npos != loc)
    {
        if(nullptr == table_[loc] ) {
            // std::cout<<"line 441"<<std::endl;
            // std::cout<<"line 458 "<<loc<<std::endl;
            return loc;
        }
        // fill in the condition for this else if statement which should 
        // return 'loc' if the given key exists at this location
        else if(table_[loc]->item.first == key && !table_[loc]->deleted) {
            return loc;
        }
        loc = prober_.next();
        totalProbes_++;
    }

    return npos;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K, V, Prober, Hash, KEqual>::reportAll(std::ostream& out) const
{
	for(HASH_INDEX_T i = 0; i < CAPACITIES[mIndex_]; ++i)
	{
		if(table_[i] != nullptr)
		{
			out << "Bucket " << i << ": " << table_[i]->item.first << " " << table_[i]->item.second << std::endl;
		}
	}
}

#endif