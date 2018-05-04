#include <algorithm>

template <typename T>
Daryheap<T>::Daryheap(const std::vector<T> &nodes, int d) : nodes(nodes), d(d)
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
T Daryheap<T>::top() const
{
    return nodes.front();
}

template <typename T>
void Daryheap<T>::push(T val)
{
}

template <typename T>
void Daryheap<T>::pop()
{
    nodes[0] = nodes.back();
    heapify(0);
    nodes.pop_back();
}

template <typename T>
void Daryheap<T>::heapify(int i)
{
    int root = i;
    int end = std::min(right(i), size());
    for (int j = left(i); j < end; j++)
    {
        if (nodes[j] < nodes[root])
        {
            root = j;
        }
    }
    if (root != i)
    {
        std::swap(nodes[i], nodes[root]);
        heapify(root);
    }
}

template <typename T>
int Daryheap<T>::parent(int i)
{
    return (i - 1) / d;
}

template <typename T>
int Daryheap<T>::left(int i)
{
    return d * i + 1;
}

template <typename T>
int Daryheap<T>::right(int i)
{
    return d * i + d;
}

template <typename T>
void Daryheap<T>::increase_priority(int i, T priority)
{
    if (priority < nodes[i])
    {
        nodes[i] = priority;
        while (i && nodes[i] < nodes[parent(i)])
        {
            std::swap(nodes[i], nodes[parent(i)]);
            i = parent(i);
        }
    }
}