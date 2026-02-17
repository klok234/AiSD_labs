#ifndef MYSET
#define MYSET

#include <iostream>
#include <exception>


size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

struct Node
{
    int value = 0;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node() = default;
    Node(int value) : value(value), left(nullptr), right(nullptr), height(0) {}
    Node(int value, Node* left, Node* right) : value(value), left(left), right(right), height(0) {}
};


class Set
{
private:

    Node* _root = nullptr;

    void delete_tree(Node* root)
    {
        if (!root)
            return;

        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }

    Node* copy_tree(Node* other)
    {
        if (!other)
            return nullptr;
        Node* res = new Node(other->value);
        res->height = other->height;
        res->left = copy_tree(other->left);
        res->right = copy_tree(other->right);
        return res;
    }

    void print_tree(Node* root) const
    {
        if (!root)
            return;

        print_tree(root->left);
        std::cout << root->value;
        print_tree(root->right);
    }

    bool contains(Node* root, int key) const
    {
        if (!root)
            return false;

        if (root->value < key)
            return contains(root->right, key);

        if (root->value > key)
            return contains(root->left, key);

        return true;
    }

    int get_height(Node* root) const
    {
        return (!root) ? -1 : root->height;
    }

    void update_height(Node* root)
    {
        root->height = std::max(get_height(root->left), get_height(root->right)) + 1;
    }

    int get_balance(Node* root) const
    {
        return (!root) ? 0 : get_height(root->right) - get_height(root->left);
    }

    void right_rotate(Node* root)
    {
        std::swap(root->value, root->left->value);
        Node* tmp = root->right;
        root->right = root->left;
        root->left = root->right->left;
        root->right->left = root->right->right;
        root->right->right = tmp;
        update_height(root->right);
        update_height(root);
    }

    void left_rotate(Node* root)
    {
        std::swap(root->value, root->right->value);
        Node* tmp = root->left;
        root->left = root->right;
        root->right = root->left->right;
        root->left->right = root->left->left;
        root->left->left = tmp;
        update_height(root->left);
        update_height(root);
    }

    void balance(Node* root)
    {
        int balance = get_balance(root);
        if (balance == -2)
        {
            if (get_balance(root->left) == 1)
                left_rotate(root->left);
            right_rotate(root);
        }
        else if (balance == 2)
        {
            if (get_balance(root->left) == -1)
                right_rotate(root->left);
            left_rotate(root);
        }
    }

    void insert(Node* root, int value)
    {
        if (value < root->value)
        {
            if (!(root->left))
                root->left = new Node(value);

            else insert(root->left, value);
        }
        else if (value > root->value)
        {
            if (!(root->right))
                root->right = new Node(value);

            else insert(root->right, value);
        }
        update_height(root);
        balance(root);
    }

    Node* get_max(Node* root)
    {
        if (!root)
            return nullptr;
        if (!root->right)
            return root;
        return get_max(root->right);
    }

    Node* erase(Node* root, int value)
    {
        if (!root)
            return nullptr;
        else if (value < root->value)
            root->left = erase(root->left, value);
        else if (value > root->value)
            root->right = erase(root->right, value);
        else
        {
            if (!root->left || !root->right)
                root = (!root->left) ? root->right : root->left;
            else
            {
                Node* max_in_left = get_max(root->left);
                root->value = max_in_left->value;
                root->left = erase(root->left, max_in_left->value);
            }
        }
        if (root)
        {
            update_height(root);
            balance(root);
        }
        return root;
    }


public:
    Set() = default;

    Set(const Set& other)
    {
        _root = new Node();
        copy_tree(other._root);
    }

    Set& operator=(const Set& other)
    {
        if (this != &other)
        {
            Set tmp(other);
            std::swap(tmp._root, this->_root);
            return *this;
        }
    }

    void print() const
    {
        print_tree(_root);
    }

    bool insert(int key)
    {
        if (contains(_root, key))
            return false;
        if (!_root)
        {
            _root = new Node(key);
            update_height(_root);
            return true;
        }
        insert(_root, key);
        return true;
    }

    bool contains(int key) const
    {
        return contains(_root, key);
    }

    bool erase(int key)
    {
        if (!contains(_root, key))
            return false;

        _root = erase(_root, key);
        return true;
    }

    bool strictly_balanced() const
    {
        return (!get_balance(_root));
    }

    ~Set() {
        delete_tree(_root);
    }
};


#endif
