#include <iostream>

template <typename T>
Fibonacci<T>::Fibonacci() : root(nullptr) {}

template <typename T>
Fibonacci<T>::Fibonacci(std::function<bool(T const &, T const &)> comp) : root(nullptr)
{
}

template <typename T>
bool Fibonacci<T>::empty() const
{
    return false;
}

template <typename T>
unsigned int Fibonacci<T>::size() const
{
    return n;
}

template <typename T>
const T Fibonacci<T>::top() const
{
    return root->key;
}

template <typename T>
void Fibonacci<T>::push(T key)
{
    Node *node = new Node(key);
    push(node);
}

template <typename T>
void Fibonacci<T>::pop()
{
    Node *old = root;
    Node *curr = old->child;

    root = get_next_on_root_level();

    if (curr != nullptr)
    {
        if (root != nullptr)
        {
            curr->right = old->right;
            old->right->left = curr;
        }

        do
        {
            curr->parent = nullptr;
            curr = curr->left;
            if (curr->key < root->key)
            {
                root = curr;
            }
        } while (curr != old->child);

        if (root != nullptr)
        {
            curr->left = old->left;
            old->left->right = curr;
        }
    }
    else
    {
        old->right->left = old->left;
        old->left->right = old->right;
    }
    delete old;
}

template <typename T>
void Fibonacci<T>::decrease_key(Node *node, T key)
{
}

template <typename T>
void Fibonacci<T>::push(Node *node)
{
    if (root == nullptr)
    {
        root = node->left = node->right = node;
    }
    else
    {
        Node *root_right = root->right;
        root->right = node;
        root_right->left = node;
        node->right = root_right;
        node->left = root;

        if (node->key < root->key)
        {
            root = node;
        }
    }
    ++n;
}

template <typename T>
typename Fibonacci<T>::Node *Fibonacci<T>::get_next_on_root_level()
{
    Node *next = root->left;
    if (next != root)
    {
        Node *curr = next->left;

        while (curr != root)
        {
            if (curr->key < next->key)
            {
                next = curr;
            }
            curr = curr->left;
        }
        return next;
    }
    else
    {
        return nullptr;
    }
}

template <typename T>
Fibonacci<T>::Node::Node(T key) : key(key) {}

template <typename T>
bool Fibonacci<T>::Node::is_marked() const
{
    return marked;
}

template <typename T>
bool Fibonacci<T>::Node::get_key() const
{
    return key;
}
