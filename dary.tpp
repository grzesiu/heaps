#include <algorithm>

template <typename T>
Dary<T>::Dary(const std::vector<T> &nodes, int d) : nodes(nodes), d(d)
{
    for (int i = (size() - 2) / d; i >= 0; i--)
    {
        heapify(i);
    }
}

template <typename T>
bool Dary<T>::empty() const
{
    return nodes.empty();
}

template <typename T>
int Dary<T>::size() const
{
    return nodes.size();
}

template <typename T>
T Dary<T>::top() const {
    return nodes.front();
}

template <typename T>
void Dary<T>::push(T val) {}

template <typename T>
void Dary<T>::pop() {}

template <typename T>
void Dary<T>::heapify(int i)
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
int Dary<T>::parent(int i)
{
    return (i - 1) / d;
}

template <typename T>
int Dary<T>::left(int i)
{
    return d * i + 1;
}

template <typename T>
int Dary<T>::right(int i)
{
    return d * i + d;
}