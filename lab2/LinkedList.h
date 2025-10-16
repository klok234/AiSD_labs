#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <random>

template <class T>
struct Node {
    T value;
    Node* next;
    Node* prev;
    Node() = delete;
    Node(T value, Node* next, Node* prev) : value(value), next(next), prev(prev){}
    Node(T value) : value(value), next(nullptr), prev(nullptr){}
};


template <class T>
class LinkedList {
    Node<T>* _head;

public:
    LinkedList() : _head(nullptr) {}
    LinkedList(const LinkedList& other)
    {
        Node<T>* iter_other = other._head;
        if (!iter_other)
        {
            _head = nullptr;
        }
        else
        {
            _head = new Node<T>(other._head->value);
            Node<T>* iter = _head;

            iter_other = iter_other->next;
            while (iter_other != other._head)
            {
                iter->next = new Node<T>(iter_other->value, nullptr, iter);
                iter_other = iter_other->next;
                iter = iter->next;
            }
            iter->next = _head;
            _head->prev = iter;
        }
    }
    LinkedList(size_t length, T start, T end, size_t seed)
    {
        if (length == 0)
        {
            _head = nullptr;
        }
        std::default_random_engine engine(seed);
        std::uniform_real_distribution distribution(std::min(start, end), std::max(start, end));

        _head = new Node<T>(static_cast<T>(distribution(engine)));
        Node<T>* iter = _head;

        for (size_t i = 0; i < length - 1; i++)
        {
            iter->next = new Node<T>(static_cast<T>(distribution(engine)), nullptr, iter);
            iter = iter->next;
        }
        iter->next = _head;
        _head->prev = iter;
    }

    void push_tail(const T& value)
    {
        Node<T>* new_node = new Node<T>(value, _head, _head->prev);
        _head->prev->next = new_node;
        _head->prev = new_node;
    }

    void push_tail(const LinkedList<T>& list)
    {
        LinkedList<T> tmp(list);
        Node<T>* tmp_tail = tmp._head->prev;
        _head->prev->next = tmp._head;
        tmp._head->prev = _head-prev;
        tmp_tail->next = _head;
        _head->prev = tmp_tail;
        tmp._head = nullptr;
    }

    void push_head(const T& value)
    {
        Node<T>* new_node = new Node<T>(value, _head, _head->prev);
        _head->prev->next = new_node;
        _head->prev = new_node;
        _head = new_node;
    }

    void push_head(const LinkedList<T>& list)
    {
        LinkedList<T> tmp(list);
        Node<T>* tmp_tail = tmp._head->prev;
        _head->prev->next = tmp._head;
        tmp._head->prev = _head - prev;
        tmp_tail->next = _head;
        _head->prev = tmp_tail;
        _head = tmp._head;
        tmp._head = nullptr;
    }

    ~LinkedList()
    {
        if (!_head)
        {
            _head->prev->next = nullptr;
            while (_head->next)
            {
                _head = _head->next;
                delete _head->prev;
            }
            delete _head;
        }
    }
};

#endif
