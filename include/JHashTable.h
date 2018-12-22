#ifndef JHASHTABLE_H
#define JHASHTABLE_H
#include "../src/JHashBucket.h"

template <typename Key, typename Value>
struct KeyValuePair {
    const Key *key;
    Value *value;
};

template <typename Key,
          typename Value,
          typename Hash,
          typename KeyEqual
> class JHashTable {
typedef JHashBucket<Key, Value, KeyEqual> Bucket;
public:
    // typedef
    typedef typename Bucket::key_type key_type;
    typedef typename Bucket::value_type  value_type;
    typedef KeyValuePair<Key, Value> table_type;
    typedef typename Bucket::size_type size_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef typename Bucket::reference reference;
    typedef typename Bucket::const_reference const_reference;

    // constructor
    explicit JHashTable(size_type bucket_count,
                        const Hash &hash = Hash(),
                        const KeyEqual &equal = KeyEqual());

    // destructor
    ~JHashTable();

    // find an element
    KeyValuePair<Key, Value> find(const key_type &key);

    // insert an element
    void insert(const key_type &key, const value_type &value);
    void force_insert(const key_type &key, const value_type &value);

    // size
    size_type size() const;

    size_type empty_bucket_count() const;

private:
    // Bucket array
    Bucket *_buckets = nullptr;
    size_type _bucket_size = 0;
    size_type _size = 0;


    key_equal _equal;
    hasher _hash;
};

/**
 * @brief Constructor
 */
template<typename Key, typename Value, typename Hash, typename KeyEqual>
JHashTable<Key, Value, Hash, KeyEqual>::JHashTable(JHashTable::size_type bucket_count,
        const Hash &hash,
        const KeyEqual &equal): _bucket_size(bucket_count), _hash(hash), _equal(equal) {
    _buckets = new Bucket[bucket_count];
}

/**
 * @brief Destructor
 */
template<typename Key, typename Value, typename Hash, typename KeyEqual>
JHashTable<Key, Value, Hash, KeyEqual>::~JHashTable() {
    delete [] _buckets;
}

/**
 * @brief find the key-value pair according to the key value, the pointer in the pair will be nullptr if not found
 * @tparam Key
 * @tparam Value
 * @tparam Hash
 * @tparam KeyEqual
 * @param key
 * @return
 */
template<typename Key, typename Value, typename Hash, typename KeyEqual>
KeyValuePair<Key, Value> JHashTable<Key, Value, Hash, KeyEqual>::find(const key_type &key) {
    size_type hash_value = _hash(key) % _bucket_size;
    typename Bucket::Node *ptr = _buckets[hash_value].find(key, _equal);
    if (ptr == nullptr) {
        return table_type{nullptr, nullptr};
    } else {
        return table_type{&ptr->key, &ptr->value};
    }
}

/**
 * @brief insert a key-value pair in the hash table, this will check if there already exist a key identical to the key provided
 */
template<typename Key, typename Value, typename Hash, typename KeyEqual>
void JHashTable<Key, Value, Hash, KeyEqual>::insert(const key_type &key, const value_type &value) {
    size_type hash_value = _hash(key) % _bucket_size;
    _buckets[hash_value].insert(key, value, _equal);
    ++_size;
}

/**
 * @brief insert a key-value pair in the hash table, this will not check anything, so the user should be aware of if there already exist an identical key
 * @tparam Key
 * @tparam Value
 * @tparam Hash
 * @tparam KeyEqual
 * @param key
 * @param value
 */
template<typename Key, typename Value, typename Hash, typename KeyEqual>
void JHashTable<Key, Value, Hash, KeyEqual>::force_insert(const key_type &key, const value_type &value) {
    size_type hash_value = _hash(key) % _bucket_size;
    _buckets[hash_value].force_insert(key, value);
    ++_size;
}

template<typename Key, typename Value, typename Hash, typename KeyEqual>
typename JHashTable<Key, Value, Hash, KeyEqual>::size_type
JHashTable<Key, Value, Hash, KeyEqual>::empty_bucket_count() const {
    size_type ret = 0;
    for (int i = 0; i < _bucket_size; i++) {
        if (_buckets[i].size() == 0)
            ++ret;
    }
    return ret;
}

template<typename Key, typename Value, typename Hash, typename KeyEqual>
typename JHashTable<Key, Value, Hash, KeyEqual>::size_type JHashTable<Key, Value, Hash, KeyEqual>::size() const {
    return _size;
}

#endif // JHASHTABLE_H