#include <algorithm>

template <typename T>
Daryheap<T>::Daryheap(const std::vector<Darynode<T> *> nodes, int d) : nodes(nodes), d(d)
{
    for (int i = (size() - 2) / d; i >= 0; i--)
    {
        heapify(i);
    }
}

template <typename T>
bool Daryheap<T>::empty() const
{
    return nodes.empty();
}

template <typename T>
int Daryheap<T>::size() const
{
    return nodes.size();
}

template <typename T>
Darynode<T> *Daryheap<T>::top() const
{
    return nodes.front();
}

template <typename T>
void Daryheap<T>::push(Darynode<T> *node)
{
}

template <typename T>
void Daryheap<T>::pop()
{
    delete nodes[0];
    nodes[0] = nodes.back();
    nodes[0]->i = 0;
    heapify(0);
    nodes.pop_back();
}

template <typename T>
void Daryheap<T>::heapify(int i)
{
    int root = i;
    int end = std::min(right_index(i), size() - 1);
    for (int j = left_index(i); j <= end; j++)
    {
        if (nodes[j]->key < nodes[root]->key)
        {
            root = j;
        }
    }
    if (root != i)
    {
        swap_indices(i, root);
        heapify(root);
    }
}

template <typename T>
void Daryheap<T>::increase_priority(Darynode<T> *node, T key)
{
    if (key < node->key)
    {
        node->key = key;
        while (node->i && node->key < nodes[parent_index(node->i)]->key)
        {
            swap_indices(node->i, parent_index(node->i));
            node = nodes[parent_index(node->i)];
        }
    }
}

template <typename T>
void Daryheap<T>::erase(Darynode<T> *node)
{
}

template <typename T>
int Daryheap<T>::parent_index(int i)
{
    return (i - 1) / d;
}

template <typename T>
int Daryheap<T>::left_index(int i)
{
    return d * i + 1;
}

template <typename T>
int Daryheap<T>::right_index(int i)
{
    return d * i + d;
}

template <typename T>
void Daryheap<T>::swap_indices(int i, int j)
{
    std::swap(nodes[i]->i, nodes[j]->i);
    std::swap(nodes[i], nodes[j]);
}