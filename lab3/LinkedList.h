#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <random>
#include <stdexcept>

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
std::ostream& operator<<(std::ostream& os, const Node<T>& node)
{
    return (os << node.value);
}

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
                iter->next = new Node<T>(iter_other->value, _head, iter);
                iter_other = iter_other->next;
                iter = iter->next;
            }
            _head->prev = iter;
        }
    }
    LinkedList(size_t length, T start, T end, unsigned int seed)
    {
        if (length == 0)
        {
            _head = nullptr;
        }
        else {
            std::default_random_engine engine(seed);
            std::uniform_real_distribution distribution(std::min(static_cast<double>(start), static_cast<double>(end)), std::max(static_cast<double>(start), static_cast<double>(end)));

            _head = new Node<T>(static_cast<T>(distribution(engine)));
            Node<T>* iter = _head;

            for (size_t i = 0; i < length - 1; i++)
            {
                iter->next = new Node<T>(static_cast<T>(distribution(engine)), _head, iter);
                iter = iter->next;
            }
            _head->prev = iter;
        }
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
        tmp._head->prev = _head->prev;
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
        tmp._head->prev = _head->prev;
        tmp_tail->next = _head;
        _head->prev = tmp_tail;
        _head = tmp._head;
        tmp._head = nullptr;
    }

    void pop_tail()
    {
        if (!_head)
        {
            return;
        }
        Node<T>* tmp = _head->prev;
        if (tmp == _head)
        {
            _head = nullptr;
            return;
        }
        _head->prev = _head->prev->prev;
        tmp->prev->next = _head;
        delete tmp;
    }

    void pop_head()
    {
        if (!_head)
        {
            return;
        }
        _head = _head->next;
        this->pop_tail();
    }

    void delete_node(const T& value)
    {
        if (!_head)
        {
            return;
        }
        Node<T>* iter = _head->next;
        while (iter != _head)
        {
            if (iter->value == value)
            {
                Node<T>* tmp = iter;
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                iter = iter->next;
                delete tmp;
                continue;
            }
            iter = iter->next;
        }
        if (_head->value == value)
        {
            this->pop_head();
        }
    }

    T operator[](size_t index) const
    {
        if (!_head)
        {
            throw std::range_error("Empty list");
        }
        Node<T>* iter = _head->next;
        for (size_t i = 0; i < index; i++)
        {
            if (iter == _head)
            {
                throw std::range_error("Out of range");
            }
            iter = iter->next;
        }
        return iter->value;
    }

    T& operator[](size_t index)
    {
        if (!_head)
        {
            throw std::range_error("Empty list");
        }
        Node<T>* iter = _head->next;
        for (size_t i = 0; i < index; i++)
        {
            if (iter == _head)
            {
                throw std::range_error("Out of range");
            }
            iter = iter->next;
        }
        return iter->prev->value;
    }

    LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        LinkedList<T> tmp(rhs);
        std::swap(_head, tmp._head);
        return *this;
    }

    void reverse()
    {
        if (!_head)
        {
            return;
        }
        Node<T>* iter = _head->next;
        while (iter != _head)
        {
            std::swap(iter->next, iter->prev);
            iter = iter->prev;
        }
        std::swap(_head->next, _head->prev);
        _head = _head->next;
    }

    const Node<T>* get_head() const
    {
        return _head;
    }

    Node<T>* get_head()
    {
        return _head;
    }

    ~LinkedList()
    {
        if (_head)
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

template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    const Node<T>* head = list.get_head();
    if (!head)
    {
        return os;
    }
    os << "{ " << *head << " ";
    Node<T>* iter = head->next;
    while (iter != head)
    {
        os << *iter << " ";
        iter = iter->next;
    }
    os << "}\n";
    return os;
}

#endif
