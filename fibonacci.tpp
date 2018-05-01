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
        root = node;
        node->left = node;
        node->right = node;
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
unsigned int Fibonacci<T>::get_max_degree() const
{
    return static_cast<unsigned int>(
        std::ceil(std::log(static_cast<double>(n)) /
                  std::log(static_cast<double>(1 + std::sqrt(static_cast<double>(5))) / 2)));
}

template <typename T>
void Fibonacci<T>::consolidate()
{
    unsigned int max_degree = get_max_degree() + 1;
    Node **nodes = new Node *[max_degree]();
    Node *curr = root;
    unsigned int root_list_size = 0;

    do
    {
        root_list_size++;
        curr = curr->left;
    } while (curr != root);

    Node **root_list = new Node *[root_list_size];

    for (int i = 0; i < root_list_size; i++)
    {
        root_list[i] = curr;
        curr = curr->left;
    }

    for (int i = 0; i < root_list_size; i++)
    {
        curr = root_list[i];
        while (nodes[curr->degree] != nullptr)
        {
            if (curr->key < nodes[curr->degree]->key)
            {
                curr = merge(curr, nodes[curr->degree]);
            }
            else
            {
                curr = merge(nodes[curr->degree], curr);
            }
            nodes[curr->degree] = nullptr;
            curr->degree++;
        }
        nodes[curr->degree] = curr;
    }

    root = nullptr;

    for (int i = 0; i < max_degree; i++)
    {
        if (nodes[i] != nullptr)
        {
            if (root == nullptr)
            {
                root = nodes[i];
                root->left = nodes[i];
                root->right = nodes[i];
            }
            else
            {
                root->left->right = nodes[i];
                nodes[i]->left = root->left;
                root->left = nodes[i];
                nodes[i]->right = root;
                if (nodes[i]->key < root->key)
                {
                    root = nodes[i];
                }
            }
        }
    }
    delete[] nodes;
}

template <typename T>
typename Fibonacci<T>::Node *Fibonacci<T>::merge(Node *parent, Node *child)
{
    child->right->left = child->left;
    child->left->right = child->right;
    if (parent->child == nullptr)
    {
        parent->child = child;
        child->left = child;
        child->right = child;
    }
    else
    {
        parent->child->left->right = child;
        child->left = parent->child->left;
        parent->child->left = child;
        child->right = parent->child;
    }
    child->parent = parent;
    child->marked = false;
    return parent;
}