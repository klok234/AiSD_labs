#ifndef UNORDERED_MAP
#define UNORDERED_MAP

#include <iostream>
#include <exception>
#include <cmath>


template <class T>
struct Node {
    int key = 0;
    T value = T(0);
    Node<T>* next = nullptr;
    Node() = default;
    Node(int key, T value) : key(key), value(value), next(nullptr) {}
};

template <class T>
class UnorderedMap
{
    Node<T>** _table = nullptr;
    size_t _capacity = 0;
    size_t hash(int key) {
        double p = (std::sqrt(5.0) - 1.0) / 2.0 * static_cast<double>(1ULL << 32) * static_cast<double>(key);
        double frac = p - std::floor(p);
        return static_cast<size_t>(std::floor(_capacity * frac));
    }
public:
    UnorderedMap(size_t capacity) : _capacity(capacity)
    {
        _table = new Node<T>*[_capacity];
        for (size_t i = 0; i < _capacity; i++)
            _table[i] = nullptr;
    }

    UnorderedMap(const UnorderedMap<T>& other) : _capacity(other._capacity)
    {
        _table = new Node<T>*[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            if (other._table[i] == nullptr) {
                _table[i] = nullptr;
                continue;
            }
            _table[i] = new Node<T>*(other._table[i]->key, other._table[i]->value);
            Node<T>* iter = _table[i];
            Node<T>* other_iter = other._table[i]->next;
            while (other_iter)
            {
                iter->next = new Node(other_iter->key, other_iter->value);
                other_iter = other_iter->next;
                iter = iter->next;
            }
        }
    }

    UnorderedMap<T>& operator=(const UnorderedMap<T>& other)
    {
        if (this != &other)
        {
            UnorderedMap<T> tmp(other);
            std::swap(_table, tmp._table);
            std::swap(_capacity, tmp._capacity);
            return *this;
        }
    }


    void print() const
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            Node<T>* iter = _table[i];
            while (iter)
            {
                std::cout << "{" << iter->key << " : " << iter->value << "} ";
                iter = iter->next;
            }
        }
        std::cout << "\n";
    }

    bool insert(int key, const T& value)
    {
        Node<T>* iter = _table[hash(key)];
        if (!iter)
        {
            _table[hash(key)] = new Node<T>(key, value);
            return true;
        }

        while (iter)
        {
            if (iter->key == key)
            {
                return false;
            }
            if (iter->next == nullptr)
                break;
            iter = iter->next;
        }
        iter->next = new Node<T>(key, value);
        return true;
    }

    void insert_or_assign(int key, const T& value)
    {
        Node<T>* iter = _table[hash(key)];
        if (!iter)
        {
            _table[hash(key)] = new Node<T>(key, value);
            return;
        }

        while (iter)
        {
            if (iter->key == key)
            {
                iter->value = value;
                return;
            }
            if (iter->next == nullptr)
                break;
            iter = iter->next;
        }
        iter->next = new Node<T>(key, value);
    }

    bool contains(T& value) const
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            Node<T>* iter = _table[i];
            while (iter)
            {
                if (iter->value == value)
                {
                    return true;
                }
                iter = iter->next;
            }
        }
        return false;
    }


    Node<T>* search(int key)
    {
        Node<T>* iter = _table[hash(key)];
        while (iter)
        {
            if (iter->key == key)
            {
                return iter;
            }
            iter = iter->next;
        }
        return nullptr;
    }

    bool erase(int key)
    {
        Node<T>* iter = _table[hash(key)];
        if (iter->is_used)
        {
            if (!iter->next)
            {
                delete iter;
                _table[hash(key)] = new Node<T>*();
                return true;
            }
            while (iter)
            {
                if (iter->key == key)
                {
                    Node<T>* tmp = iter;
                    iter = iter->next;
                    delete tmp;
                    return true;
                }
                iter = iter->next;
            }
        }
        return false;
    }


    int count(int key) const
    {
        Node<T>* iter = _table[hash(key)];
        int result = 0;
        while (iter)
        {
            result++;
            iter = iter->next;
        }
        return result;
    }

    ~UnorderedMap()
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            Node<T>* head = _table[i];
            while (head)
            {
                Node<T>* next = head->next;
                delete head;
                head = next;
            }
        }
        delete[] _table;
    }

};


#endif
