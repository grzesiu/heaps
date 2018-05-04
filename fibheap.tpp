#include <cmath>
#include <limits>

template <typename T>
Fibheap<T>::Fibheap() : root(nullptr) {}

template <typename T>
Fibheap<T>::Fibheap(std::function<bool(T const &, T const &)> comp) : root(nullptr)
{
}

template <typename T>
bool Fibheap<T>::empty() const
{
    return false;
}

template <typename T>
int Fibheap<T>::size() const
{
    return n;
}

template <typename T>
Fibnode<T> *Fibheap<T>::top() const
{
    return root;
}

template <typename T>
Fibnode<T> *Fibheap<T>::push(T key)
{
    Fibnode<T> *node = new Fibnode<T>(key);
    return push(node);
}

template <typename T>
void Fibheap<T>::pop()
{
    if (root != nullptr)
    {
        Fibnode<T> *curr = root->child;
        if (curr != nullptr)
        {
            Fibnode<T> **children = new Fibnode<T> *[root->degree]();
            for (int i = 0; i < root->degree; i++)
            {
                children[i] = curr;
                curr = curr->left;
            }
            for (int i = 0; i < root->degree; i++)
            {
                insert(root, children[i]);
                children[i]->parent = nullptr;
            }
            delete[] children;
        }

        Fibnode<T> *old_root = root;

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
void Fibheap<T>::increase_priority(Fibnode<T> *node, T key)
{
    if (key < node->key)
    {
        node->key = key;
        if (node->parent != nullptr && node->key < node->parent->key)
        {
            cut(node, node->parent);
            cascading_cut(node->parent);
        }
        if (node->key < root->key)
        {
            root = node;
        }
    }
}

template <typename T>
void Fibheap<T>::erase(Fibnode<T> *node)
{
    increase_priority(node, std::numeric_limits<T>::min());
    pop();
}

template <typename T>
Fibnode<T> *Fibheap<T>::push(Fibnode<T> *node)
{
    if (root == nullptr)
    {
        root = node;
        node->left = node;
        node->right = node;
    }
    else
    {
        insert(root, node);
        if (node->key < root->key)
        {
            root = node;
        }
    }
    ++n;
    return node;
}

template <typename T>
int Fibheap<T>::get_max_degree() const
{
    return static_cast<int>(
        std::ceil(std::log(static_cast<double>(n)) /
                  std::log(static_cast<double>(1 + std::sqrt(static_cast<double>(5))) / 2)));
}

template <typename T>
void Fibheap<T>::consolidate()
{
    int max_degree = get_max_degree() + 1;
    Fibnode<T> **nodes = new Fibnode<T> *[max_degree]();
    Fibnode<T> *curr = root;
    int root_list_size = 0;

    do
    {
        root_list_size++;
        curr = curr->left;
    } while (curr != root);

    Fibnode<T> **root_list = new Fibnode<T> *[root_list_size];

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
                insert(root, nodes[i]);
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
Fibnode<T> *Fibheap<T>::merge(Fibnode<T> *parent, Fibnode<T> *child)
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
        insert(parent->child, child);
    }
    child->parent = parent;
    child->marked = false;
    return parent;
}

template <typename T>
void Fibheap<T>::insert(Fibnode<T> *parent, Fibnode<T> *child)
{
    parent->left->right = child;
    child->left = parent->left;
    parent->left = child;
    child->right = parent;
}

template <typename T>
void Fibheap<T>::cut(Fibnode<T> *parent, Fibnode<T> *child)
{
    if (child->left == child)
    {
        parent->child = nullptr;
    }
    else
    {
        child->right->left = child->left;
        child->left->right = child->right;
        if (parent->child == child)
        {
            parent->child = child->left;
        }
    }
    parent->degree--;

    insert(root, child);
    child->parent = nullptr;
    child->marked = false;
}

template <typename T>
void Fibheap<T>::cascading_cut(Fibnode<T> *node)
{
    if (node->parent != nullptr)
    {
        if (node->marked)
        {
            cut(node->parent, node);
            cascading_cut(node->parent);
        }
        else
        {
            node->marked = true;
        }
    }
}