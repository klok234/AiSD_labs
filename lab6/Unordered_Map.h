#ifndef UNORDERED_MAP
#define UNORDERED_MAP

#include <iostream>
#include <functional>   
#include <vector>
#include <utility>      

template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template<
    typename Key,
    typename Value,
    typename Hash = std::hash<Key>     
>
class UnorderedMap {
private:
    using NodeType = Node<Key, Value>;
    NodeType** _buckets;        
    size_t      _bucketCount;   
    size_t      _size;          
    Hash        _hasher;        

    size_t bucketIndex(const Key& key) const {
        return _hasher(key) % _bucketCount;
    }

    void rehash(size_t newBucketCount) {
        NodeType** newBuckets = new NodeType * [newBucketCount]();
        NodeType** oldBuckets = _buckets;
        size_t oldCount = _bucketCount;

        for (size_t i = 0; i < oldCount; ++i) {
            NodeType* node = oldBuckets[i];
            while (node) {
                NodeType* nextNode = node->next;

                size_t newIdx = _hasher(node->key) % newBucketCount;
                node->next = newBuckets[newIdx];
                newBuckets[newIdx] = node;

                node = nextNode;
            }
        }

        delete[] oldBuckets;
        _buckets = newBuckets;
        _bucketCount = newBucketCount;
    }

public:
    UnorderedMap(size_t initialCapacity = 16)
        : _bucketCount(initialCapacity), _size(0), _hasher(Hash()) {
        _buckets = new NodeType * [_bucketCount]();
    }

    UnorderedMap(const UnorderedMap& other)
        : _bucketCount(other._bucketCount), _size(other._size), _hasher(other._hasher) {
        _buckets = new NodeType * [_bucketCount]();
        for (size_t i = 0; i < _bucketCount; ++i) {
            NodeType* src = other._buckets[i];
            if (!src) continue;

            NodeType* dst = new NodeType(src->key, src->value);
            _buckets[i] = dst;
            src = src->next;

            while (src) {
                dst->next = new NodeType(src->key, src->value);
                dst = dst->next;
                src = src->next;
            }
        }
    }

    UnorderedMap& operator=(const UnorderedMap& other) {
        if (this != &other) {
            UnorderedMap tmp(other);
            swap(tmp);
        }
        return *this;
    }

    void swap(UnorderedMap& other) noexcept {
        std::swap(_buckets, other._buckets);
        std::swap(_bucketCount, other._bucketCount);
        std::swap(_size, other._size);
        std::swap(_hasher, other._hasher);
    }

    ~UnorderedMap() {
        clear();
        delete[] _buckets;
    }

    void clear() {
        for (size_t i = 0; i < _bucketCount; ++i) {
            NodeType* node = _buckets[i];
            while (node) {
                NodeType* toDelete = node;
                node = node->next;
                delete toDelete;
            }
            _buckets[i] = nullptr;
        }
        _size = 0;
    }

    bool insert(const Key& key, const Value& val) {
        size_t idx = bucketIndex(key);
        NodeType* node = _buckets[idx];
        while (node) {
            if (node->key == key) return false;
            node = node->next;
        }
        NodeType* newNode = new NodeType(key, val);
        newNode->next = _buckets[idx];
        _buckets[idx] = newNode;
        ++_size;
        return true;
    }

    void insert_or_assign(const Key& key, const Value& val) {
        size_t idx = bucketIndex(key);
        NodeType* node = _buckets[idx];
        while (node) {
            if (node->key == key) {
                node->value = val;
                return;
            }
            node = node->next;
        }
        NodeType* newNode = new NodeType(key, val);
        newNode->next = _buckets[idx];
        _buckets[idx] = newNode;
        ++_size;
    }

    Value* find(const Key& key) {
        size_t idx = bucketIndex(key);
        NodeType* node = _buckets[idx];
        while (node) {
            if (node->key == key) return &node->value;
            node = node->next;
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        size_t idx = bucketIndex(key);
        NodeType* node = _buckets[idx];
        while (node) {
            if (node->key == key) return &node->value;
            node = node->next;
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        size_t idx = bucketIndex(key);
        NodeType* prev = nullptr;
        NodeType* curr = _buckets[idx];
        while (curr) {
            if (curr->key == key) {
                if (prev)
                    prev->next = curr->next;
                else
                    _buckets[idx] = curr->next;
                delete curr;
                --_size;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    bool contains(const Key& key) const {
        return find(key) != nullptr;
    }

    Value& operator[](const Key& key) {
        Value* ptr = find(key);
        if (ptr) return *ptr;
        insert(key, Value());
        return *find(key);
    }

    void reserve(size_t newBucketCount) {
        if (newBucketCount <= _bucketCount) return;
        rehash(newBucketCount);
    }

    size_t size() const { return _size; }

    size_t bucket_count() const { return _bucketCount; }


    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(NodeType** buckets, size_t bucketCount, size_t curBucket, NodeType* curNode)
            : _buckets(buckets), _bucketCount(bucketCount), _curBucket(curBucket), _curNode(curNode) {
            if (_curNode == nullptr && _curBucket < _bucketCount) advanceToNextValid();
        }

        reference operator*() const { return _pair; }
        pointer operator->() const { return &_pair; }

        Iterator& operator++() {
            if (_curNode) _curNode = _curNode->next;
            advanceToNextValid();
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return _curBucket == other._curBucket && _curNode == other._curNode;
        }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        NodeType** _buckets;
        size_t _bucketCount;
        size_t _curBucket;
        NodeType* _curNode;
        std::pair<Key, Value> _pair;

        void advanceToNextValid() {
            while (_curBucket < _bucketCount && _curNode == nullptr) {
                _curNode = _buckets[_curBucket];
                if (_curNode == nullptr) ++_curBucket;
            }
            if (_curNode) {
                _pair = std::pair<Key, Value>(_curNode->key, _curNode->value);
            }
        }
    };

    Iterator begin() {
        return Iterator(_buckets, _bucketCount, 0, nullptr);
    }

    Iterator end() {
        return Iterator(_buckets, _bucketCount, _bucketCount, nullptr);
    }
};

#endif
