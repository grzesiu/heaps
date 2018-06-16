#include <algorithm>

template<typename I, typename K>
Daryheap<I, K>::Daryheap(int d) : d(d) {
}

template<typename I, typename K>
bool Daryheap<I, K>::empty() const {
    return nodes.empty();
}

template<typename I, typename K>
int Daryheap<I, K>::size() const {
    return nodes.size();
}

template<typename I, typename K>
std::pair <I, K> Daryheap<I, K>::top() const {
    return std::make_pair(nodes.front().id, nodes.front().key);
}

template<typename I, typename K>
void Daryheap<I, K>::create(const std::set <I> &ids, K max) {
    nodes.reserve(ids.size());
    for (auto id :ids) {
        nodes.push_back(Darynode<I, K>(id, max));
    }
    for (int i = (size() - 2) / d; i >= 0; i--) {
        heapify(i);
    }
}

template<typename I, typename K>
void Daryheap<I, K>::push(I id, K key) {
    nodes.push_back(Darynode<I, K>(id, key));
    indices[id] = nodes.size() - 1;

    while (indices[id] && nodes[indices[id]].key < nodes[parent_index(indices[id])].key) {
        swap(indices[id], parent_index(indices[id]));
    }
}

template<typename I, typename K>
void Daryheap<I, K>::pop() {
    indices.erase(nodes[0].id);
    nodes[0] = nodes.back();
    nodes.pop_back();
    indices[nodes[0].id] = 0;
    heapify(0);
}

template<typename I, typename K>
void Daryheap<I, K>::heapify(int i) {
    int root = i;
    int end = std::min(right_index(i), size() - 1);
    for (int j = left_index(i); j <= end; j++) {
        if (nodes[j].key < nodes[root].key) {
            root = j;
        }
    }
    if (root != i) {
        swap(i, root);
        heapify(root);
    }
}

template<typename I, typename K>
void Daryheap<I, K>::increase_priority(I id, K key) {
    if (key < nodes[indices[id]].key) {
        nodes[indices[id]].key = key;
        while (indices[id] && nodes[indices[id]].key < nodes[parent_index(indices[id])].key) {
            swap(indices[id], parent_index(indices[id]));
        }
    }
}

template<typename I, typename K>
void Daryheap<I, K>::erase(I id) {
}

template<typename I, typename K>
int Daryheap<I, K>::parent_index(int i) {
    return (i - 1) / d;
}

template<typename I, typename K>
int Daryheap<I, K>::left_index(int i) {
    return d * i + 1;
}

template<typename I, typename K>
int Daryheap<I, K>::right_index(int i) {
    return d * i + d;
}

template<typename I, typename K>
void Daryheap<I, K>::swap(int i, int j) {
    std::swap(nodes[i], nodes[j]);
    std::swap(indices[nodes[i].id], indices[nodes[j].id]);
}