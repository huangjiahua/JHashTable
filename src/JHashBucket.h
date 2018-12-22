#ifndef JHASHBUCKET_H
#define JHASHBUCKET_H

template <typename Key, typename Value>
struct JHashBucketEntry {
    Key key;
    Value value;
    JHashBucketEntry *next;
};

template <typename Key, typename Value, typename Pred>
class JHashBucket {
private:
    typedef JHashBucketEntry<Key, Value> Node;
public:
    // typedef
    typedef Key key_type;
    typedef Value value_type;
    typedef unsigned long int size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    // constructor
    JHashBucket() = default;

    // destructor
    ~JHashBucket();

    // Add an element
    void insert(const key_type &key, const value_type &value, const Pred &equal);
    void force_insert(const key_type &key, const value_type &value);

    // Delete an element
    void erase(const key_type &key);

    // Find an element
    JHashBucketEntry<Key, Value> *find(const key_type &key, const Pred &equal);

    // Get the size
    inline size_type size() const;

private:
    // data members
    Node *_root = nullptr;
    size_type _size = 0;

    // private member functions
    inline void push_front(const key_type &key, const value_type &value);
};

/**
 * @brief Destructor: Free all node.
 */
template<typename Key, typename Value, typename Pred>
JHashBucket<Key, Value, Pred>::~JHashBucket() {
    Node *_curr = _root, *_next;
    while (_curr != nullptr) {
        _next = _curr->next;
        delete _curr;
        _curr = _next;
    }
}

/**
 * @brief insert: insert a key-value pair
 * @param key the key
 * @param value the value
 */
template<typename Key, typename Value, typename Pred>
void JHashBucket<Key, Value, Pred>::insert(const key_type &key, const value_type &value, const Pred &equal) {
    // find if the key already exist
    Node *_loc = find(key, equal);

    if (_loc == nullptr) {
        push_front(key, value);
    } else {
        _loc->value = value;
    }
}




/**
 * @brief private push_front: insert an entry at head
 * @param key
 * @param value
 */
template<typename Key, typename Value, typename Pred>
void JHashBucket<Key, Value, Pred>::push_front(const key_type &key, const value_type &value) {
    Node *_node = new Node{key, value, _root};
    _root = _node;
    ++_size;
}

/**
 * @brief erase: delete an element
 * @param key the key
 */
template<typename Key, typename Value, typename Pred>
void JHashBucket<Key, Value, Pred>::erase(const key_type &key) {
    // TODO
}

template<typename Key, typename Value, typename Pred>
void JHashBucket<Key, Value, Pred>::force_insert(const key_type &key,
        const value_type &value) {
    push_front(key, value);
}

template<typename Key, typename Value, typename Pred>
typename JHashBucket<Key, Value, Pred>::size_type JHashBucket<Key, Value, Pred>::size() const {
    return _size;
}

template<typename Key, typename Value, typename Pred>
JHashBucketEntry<Key, Value> *JHashBucket<Key, Value, Pred>::find(const key_type &key, const Pred &equal) {
    Node *_curr = _root;
    while (_curr != nullptr && !equal(key, _curr->key))
        _curr = _curr->next;
    return _curr;
}

#endif // JHASHBUCKET_H