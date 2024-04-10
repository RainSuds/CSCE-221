#include <cstddef>    // size_t
#include <functional> // std::hash
#include <ios>
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"



template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    size_type _bucket_count;
    HashNode **_buckets;

    HashNode * _head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    template <typename pointer_type, typename reference_type, typename _value_type>
    class basic_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap * _map;
        HashNode * _ptr;

        explicit basic_iterator(UnorderedMap const * map, HashNode *ptr) noexcept : _map(map), _ptr(ptr) { /* TODO */ }

    public:
        basic_iterator() : _map(nullptr), _ptr(nullptr) { /* TODO */ };

        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;
        reference operator*() const { /* TODO */ return _ptr->val; }
        pointer operator->() const { /* TODO */ return &(_ptr->val); }
        basic_iterator &operator++() { /* TODO */ /*prefix increment*/
            if (_ptr == nullptr) return *this;

            if (_ptr->next) { // next node
                _ptr = _ptr->next;
                return *this;
            }

            size_type current_bucket = _map->_bucket(_ptr->val); // find _bucket(pair)
            for (size_type i = current_bucket + 1; i < _map->_bucket_count; ++i) {
                if (_map->_buckets[i]) {
                    _ptr = _map->_buckets[i];
                    return *this;
                }
            }
            _ptr = nullptr;
            
            return *this;
        }
        basic_iterator operator++(int) { /* TODO */ 
            basic_iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const basic_iterator &other) const noexcept { /* TODO */ 
            return (_ptr == other._ptr);
        }
        bool operator!=(const basic_iterator &other) const noexcept { /* TODO */ 
            return !(_ptr == other._ptr);
        }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            HashNode * _node;

            explicit local_iterator( HashNode * node ) noexcept : _node(node) { /* TODO */ }

        public:
            local_iterator() : _node(nullptr) { /* TODO */ }
            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const { /* TODO */ return _node->val; }
            pointer operator->() const { /* TODO */ return &(_node->val); }
            local_iterator & operator++() { /* TODO */ 
                if (_node) {
                    _node = _node->next;
                }                
                return *this;
            }
            local_iterator operator++(int) { /* TODO */ /*post increment*/
                local_iterator temp = *this;
                ++(*this);
                return temp;
            }
            bool operator==(const local_iterator &other) const noexcept { /* TODO */ return _node == other._node; }
            bool operator!=(const local_iterator &other) const noexcept { /* TODO */ return !(_node == other._node); }
    };

private:

    size_type _bucket(size_t code) const { /* TODO */ 
        return _range_hash(code, _bucket_count);
    }
    size_type _bucket(const Key & key) const { /* TODO */ 
        size_t hash_code = _hash(key);
        return _bucket(hash_code);
    }
    size_type _bucket(const value_type & val) const { /* TODO */ 
        return _bucket(val.first);
    }

    HashNode*& _find(size_type code, size_type bucket, const Key & key) { /* TODO */
        HashNode** my_buckets = &_buckets[bucket];

        while (*my_buckets) {
            if (_equal((*my_buckets)->val.first, key)) {
                return *my_buckets;
            }
            my_buckets = &((*my_buckets)->next);
        }

        return *my_buckets;
    }

    HashNode*& _find(const Key & key) { /* TODO */ 
        size_t hash_code = _hash(key);
        size_type bucket = _bucket(hash_code);

        return _find(hash_code, bucket, key);
    }

    HashNode * _insert_into_bucket(size_type bucket, value_type && value) { /* TODO */ 
        HashNode* new_node = new HashNode(std::move(value), _buckets[bucket]);

        if (!_head || _bucket(_head->val.first) >= bucket) {
            _head = new_node;
        }
        
        // new_node->next = _buckets[bucket];
        _buckets[bucket] = new_node;
        _size++;

        return new_node;
    }

    void _move_content(UnorderedMap & src, UnorderedMap & dst) { /* TODO */ 
        dst._bucket_count = src._bucket_count;
        dst._buckets = src._buckets;
        dst._size = src._size;
        dst._head = src._head;
        src._size = 0;
        src._head = nullptr;
        src._buckets = new HashNode*[src._bucket_count]{ };
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
        const key_equal & equal = key_equal { }) : 
        _bucket_count(next_greater_prime(bucket_count)), 
        _buckets(new HashNode* [_bucket_count]{ }), 
        _head(nullptr), 
        _size(0), 
        _hash(hash), 
        _equal(equal) { /* TODO */ }

    ~UnorderedMap() { /* TODO */ 
    
        clear(); 
        delete[] _buckets;
        _buckets = nullptr;
    }    

    UnorderedMap(const UnorderedMap & other) : 
        _bucket_count(other._bucket_count), 
        _buckets(new HashNode* [other._bucket_count]{ }), 
        _head(nullptr), 
        _size(0), 
        _hash(other._hash), 
        _equal(other._equal) { /* TODO */ 

        if (&other == this) return;

        for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
            size_type bucketIndex = _bucket(it->first);
            _insert_into_bucket(bucketIndex, value_type(*it));
        }
    }

    UnorderedMap(UnorderedMap && other) :
        _bucket_count(other._bucket_count), 
        _buckets(nullptr), 
        _head(nullptr), 
        _size(0), 
        _hash(std::move(other._hash)), 
        _equal(std::move(other._equal)) { /* TODO */ 

        _move_content(other, *this);
    }

    UnorderedMap & operator=(const UnorderedMap & other) { /* TODO */ 
        if (&other != this) { 
            clear();
            delete[] _buckets;

            _bucket_count = other._bucket_count;
            _buckets = new HashNode* [_bucket_count]{ };
            _head = nullptr;
            _size = 0;
            _hash = other._hash;
            _equal = other._equal;

            for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
                size_type bucketIndex = _bucket(it->first);
                _insert_into_bucket(bucketIndex, value_type(*it));
            }          
        }
        
        return *this;
    }

    UnorderedMap & operator=(UnorderedMap && other) { /* TODO */ 
        if (&other != this) {
            clear();
            delete[] _buckets;
            _hash = std::move(other._hash);
            _equal = std::move(other._equal);

            _move_content(other, *this);
        }
        
        return *this;
    }

    void clear() noexcept { /* TODO */ 
        iterator it = begin();

        while (it != end()) {
            it = erase(it);
        }
    }

    size_type size() const noexcept { /* TODO */ return _size; }

    bool empty() const noexcept { /* TODO */ return _size ? 0:1; }

    size_type bucket_count() const noexcept { /* TODO */ return _bucket_count; }

    iterator begin() { /* TODO */ 
        if (!empty()) {
            return iterator(this, _head);
        }        

        return end();
    }
    iterator end() { /* TODO */ 
        return iterator(this, nullptr);
    }

    const_iterator cbegin() const { /* TODO */ 
        if (!empty()) {
            return const_iterator(this, _head);
        }

        return cend();
    };
    const_iterator cend() const { /* TODO */ 
        return const_iterator(this, nullptr);
    };

    local_iterator begin(size_type n) { /* TODO */ 
        if (n >= _bucket_count) {
            throw std::out_of_range("Bucket index out of range");
        }
        return local_iterator(_buckets[n]);
    }
    local_iterator end(size_type n) { /* TODO */ 
        if (n >= _bucket_count) {
            throw std::out_of_range("Bucket index out of range");
        }
        return local_iterator(nullptr);
    }

    size_type bucket_size(size_type n) { /* TODO */ 
        if (n >= _bucket_count) {
            throw std::out_of_range("Bucket index out of range");
        }

        size_type size = 0;
        HashNode* current = _buckets[n];

        while (current) {
            size++;
            current = current->next;
        }

        return size; 
    }

    float load_factor() const { /* TODO */ return bucket_count() ? (static_cast<float>(size()) / static_cast<float>(bucket_count())) : 0.0f;}

    size_type bucket(const Key & key) const { /* TODO */ return _bucket(key); }

    std::pair<iterator, bool> insert(value_type && value) { /* TODO */ 
        HashNode* nodePtr = _find(value.first);

        if (nodePtr) { // if element exist
            return std::make_pair(iterator(this, nodePtr), false);
        }
        nodePtr = _insert_into_bucket(bucket(value.first), std::move(value));
        return std::make_pair(iterator(this, nodePtr), true);
    }

    std::pair<iterator, bool> insert(const value_type & value) { /* TODO */ 
        HashNode* nodePtr = _find(value.first);

        if (nodePtr) { // if element exist
            return std::make_pair(iterator(this, nodePtr), false);
        }
        nodePtr = _insert_into_bucket(bucket(value.first), value_type(value));
        return std::make_pair(iterator(this, nodePtr), true);
    }

    iterator find(const Key & key) { /* TODO */ 
        size_type bucketIndex = bucket(key);
        HashNode* my_bucket = _buckets[bucketIndex];

        while (my_bucket) {
            if (_equal(my_bucket->val.first, key)) {
                return iterator(this, my_bucket);
            }
            my_bucket = my_bucket->next;
        }

        return end();
    }
    T& operator[](const Key & key) { /* TODO */ 
        size_type bucket = _bucket(key);
        HashNode* node = _find(key);

        if (node == nullptr) {
            value_type new_value(key, T());
            node = _insert_into_bucket(bucket, std::move(new_value));
        }

        return node->val.second;
    }

    iterator erase(iterator pos) { /* TODO */ 

        HashNode*& nodePtr = _find(pos._ptr->val.first);

        if (nodePtr == nullptr) return end();

        iterator next = ++pos;
        HashNode* toDelete = nodePtr;
        nodePtr = nodePtr->next;

        if (toDelete == _head) _head = next._ptr;
        
        delete toDelete;
        --_size;

        return next;
    }

    size_type erase(const Key & key) { /* TODO */ 
        iterator it = find(key); // the pointer

        if (it == end()) return 0;

        erase(it);
        
        return 1;
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        while(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
            node = node->next;
        }

        os << std::endl;
    }
}
