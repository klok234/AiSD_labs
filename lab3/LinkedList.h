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
    Node(T value, Node* next, Node* prev) : value(value), next(next), prev(prev) {}
    Node(T value) : value(value), next(nullptr), prev(nullptr) {}
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node)
{
    return (os << node.value);
}

template <class T>
class LinkedList {
    Node<T>* _head;
    Node<T>* _tail;

public:
    LinkedList() : _head(nullptr), _tail(nullptr) {}

    LinkedList(const LinkedList& other) : _head(nullptr), _tail(nullptr)
    {
        Node<T>* iter_other = other._head;
        while (iter_other != nullptr)
        {
            this->push_tail(iter_other->value);
            iter_other = iter_other->next;
        }
    }

    LinkedList(size_t length, T start, T end, unsigned int seed) : _head(nullptr), _tail(nullptr)
    {
        if (length == 0)
        {
            return;
        }

        std::default_random_engine engine(seed);
        std::uniform_real_distribution<double> distribution(std::min(start, end), std::max(start, end));

        for (size_t i = 0; i < length; i++)
        {
            this->push_tail(distribution(engine));
        }
    }

    void push_tail(const T& value)
    {
        Node<T>* new_node = new Node<T>(value);
        if (!_head)
        {
            _head = new_node;
            _tail = new_node;
        }
        else
        {
            _tail->next = new_node;
            new_node->prev = _tail;
            _tail = new_node;
        }
    }

    void push_tail(const LinkedList<T>& list)
    {
        Node<T>* current = list._head;
        while (current != nullptr)
        {
            this->push_tail(current->value);
            current = current->next;
        }
    }

    void push_head(const T& value)
    {
        Node<T>* new_node = new Node<T>(value);
        if (!_head)
        {
            _head = new_node;
            _tail = new_node;
        }
        else
        {
            new_node->next = _head;
            _head->prev = new_node;
            _head = new_node;
        }
    }

    void push_head(const LinkedList<T>& list)
    {
        Node<T>* current = list._tail;
        while (current != nullptr)
        {
            this->push_head(current->value);
            current = current->prev;
        }
    }

    void pop_tail()
    {
        if (!_tail) return;

        if (_head == _tail)
        {
            delete _tail;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Node<T>* new_tail = _tail->prev;
            new_tail->next = nullptr;
            delete _tail;
            _tail = new_tail;
        }
    }

    void pop_head()
    {
        if (!_head) return;

        if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Node<T>* new_head = _head->next;
            new_head->prev = nullptr;
            delete _head;
            _head = new_head;
        }
    }

    void delete_node(const T& value)
    {
        Node<T>* current = _head;
        while (current != nullptr)
        {
            if (current->value == value)
            {
                if (current == _head)
                {
                    this->pop_head();
                    current = _head;
                }
                else if (current == _tail)
                {
                    this->pop_tail();
                    current = nullptr;
                }
                else
                {
                    Node<T>* prev_node = current->prev;
                    Node<T>* next_node = current->next;
                    prev_node->next = next_node;
                    next_node->prev = prev_node;
                    delete current;
                    current = next_node;
                }
            }
            else
            {
                current = current->next;
            }
        }
    }

    T operator[](size_t index) const
    {
        if (!_head)
        {
            throw std::range_error("Empty list");
        }

        Node<T>* current = _head;
        for (size_t i = 0; i < index; i++)
        {
            if (!current->next)
            {
                throw std::range_error("Out of range");
            }
            current = current->next;
        }
        return current->value;
    }

    T& operator[](size_t index)
    {
        if (!_head)
        {
            throw std::range_error("Empty list");
        }

        Node<T>* current = _head;
        for (size_t i = 0; i < index; i++)
        {
            if (!current->next)
            {
                throw std::range_error("Out of range");
            }
            current = current->next;
        }
        return current->value;
    }

    LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        if (this != &rhs)
        {
            while (_head)
            {
                this->pop_head();
            }
            Node<T>* current = rhs._head;
            while (current != nullptr)
            {
                this->push_tail(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    void reverse()
    {
        if (!_head || !_head->next) return;

        Node<T>* current = _head;
        Node<T>* temp = nullptr;

        while (current != nullptr)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        temp = _head;
        _head = _tail;
        _tail = temp;
    }

    const Node<T>* get_head() const { return _head; }
    Node<T>* get_head() { return _head; }

    const Node<T>* get_tail() const { return _tail; }
    Node<T>* get_tail() { return _tail; }

    size_t size() const
    {
        size_t count = 0;
        Node<T>* current = _head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    bool empty() const { return _head == nullptr; }

    ~LinkedList()
    {
        while (_head != nullptr)
        {
            Node<T>* next = _head->next;
            delete _head;
            _head = next;
        }
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    const Node<T>* current = list.get_head();
    os << "{ ";
    while (current != nullptr)
    {
        os << current->value;
        if (current->next != nullptr)
        {
            os << " <-> ";
        }
        current = current->next;
    }
    os << " }";
    return os;
}

#endif
