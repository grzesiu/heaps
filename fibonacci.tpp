#include <cmath>

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
    if (root != nullptr)
    {
        Node *curr = root->child;
        if (curr != nullptr)
        {
            Node **children = new Node *[root->degree]();
            for (int i = 0; i < root->degree; i++)
            {
                children[i] = curr;
                curr = curr->left;
            }
            for (int i = 0; i < root->degree; i++)
            {
                root->left->right = children[i];
                children[i]->left = root->left;
                root->left = children[i];
                children[i]->right = root;
                children[i]->parent = nullptr;
            }
            delete[] children;
        }

        Node *old_root = root;

        if (root == root->right)
        {
            root = nullptr;
        }
        else
        {
            root->right->left = root->left;
            root->left->right = root->right;
            root = root->right;
            consolidate();
        }

        delete old_root;
        n--;
    }
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

template <typename T>
unsigned int Fibonacci<T>::max_degree() const
{
    return static_cast<unsigned int>(
        std::ceil(std::log(static_cast<double>(n)) /
                  std::log(static_cast<double>(1 + std::sqrt(static_cast<double>(5))) / 2)));
}

template <typename T>
void Fibonacci<T>::consolidate()
{
}