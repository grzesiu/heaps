#include <iostream>
#include <cmath>
#include <limits>

template<typename I, typename K>
Fibheap<I, K>::Fibheap() : root(nullptr) {}

template<typename I, typename K>
Fibheap<I, K>::Fibheap(std::function<bool(K const &, K const &)> comp) : root(nullptr) {
}

template<typename I, typename K>
Fibheap<I, K>::~Fibheap() {
    for (auto i : nodes) {
        delete i.second;
    }
}

template<typename I, typename K>
bool Fibheap<I, K>::empty() const {
    return nodes.empty();
}

template<typename I, typename K>
int Fibheap<I, K>::size() const {
    return nodes.size();
}

template<typename I, typename K>
std::pair <I, K> Fibheap<I, K>::top() const {
    return std::make_pair(root->id, root->key);
}

template<typename I, typename K>
void Fibheap<I, K>::create(const std::set <I> &ids, K max) {
    for (auto id:ids) {
        push(id, max);
    }
};

template<typename I, typename K>
void Fibheap<I, K>::push(I id, K key) {
    Fibnode <I, K> *node = new Fibnode<I, K>(id, key);
    nodes[id] = node;

    if (root == nullptr) {
        root = node;
        node->left = node;
        node->right = node;
    } else {
        insert(root, node);
        if (node->key < root->key) {
            root = node;
        }
    }
}

template<typename I, typename K>
void Fibheap<I, K>::pop() {
    if (root != nullptr) {
        Fibnode <I, K> *curr = root->child;
        if (curr != nullptr) {
            Fibnode <I, K> **children = new Fibnode <I, K> *[root->degree]();
            for (int i = 0; i < root->degree; i++) {
                children[i] = curr;
                curr = curr->left;
            }
            for (int i = 0; i < root->degree; i++) {
                insert(root, children[i]);
                children[i]->parent = nullptr;
            }
            delete[] children;
        }

        Fibnode <I, K> *old_root = root;

        if (root == root->right) {
            root = nullptr;
        } else {
            root->right->left = root->left;
            root->left->right = root->right;
            root = root->right;
            consolidate();
        }
        nodes.erase(old_root->id);
        delete old_root;
    }
}

template<typename I, typename K>
void Fibheap<I, K>::increase_priority(I id, K key) {
    Fibnode <I, K> *node = nodes[id];
    if (key < node->key) {
        node->key = key;
        Fibnode <I, K> *parent = node->parent;
        if (parent != 0 && node->key < parent->key) {
            cut(parent, node);
            cascading_cut(parent);
        }
        if (node->key < root->key) {
            root = node;
        }
    }
}

template<typename I, typename K>
void Fibheap<I, K>::erase(I id) {
    increase_priority(id, std::numeric_limits<K>::min());
    pop();
}

template<typename I, typename K>
int Fibheap<I, K>::get_max_degree() const {
    return static_cast<int>(
            std::ceil(std::log(static_cast<double>(size())) /
                      std::log(static_cast<double>(1 + std::sqrt(static_cast<double>(5))) / 2)));
}

template<typename I, typename K>
void Fibheap<I, K>::consolidate() {
    int max_degree = get_max_degree() + 1;
    Fibnode <I, K> **nodes_degree_list = new Fibnode <I, K> *[max_degree]();
    Fibnode <I, K> *curr = root;
    int root_list_size = 0;

    do {
        root_list_size++;
        curr = curr->left;
    } while (curr != root);

    Fibnode <I, K> **root_list = new Fibnode <I, K> *[root_list_size];

    for (int i = 0; i < root_list_size; i++) {
        root_list[i] = curr;
        curr = curr->left;
    }

    for (int i = 0; i < root_list_size; i++) {
        curr = root_list[i];
        while (nodes_degree_list[curr->degree] != nullptr) {
            if (curr->key < nodes_degree_list[curr->degree]->key) {
                curr = merge(curr, nodes_degree_list[curr->degree]);
            } else {
                curr = merge(nodes_degree_list[curr->degree], curr);
            }
            nodes_degree_list[curr->degree] = nullptr;
            curr->degree++;
        }
        nodes_degree_list[curr->degree] = curr;
    }

    delete[] root_list;
    root = nullptr;

    for (int i = 0; i < max_degree; i++) {
        if (nodes_degree_list[i] != nullptr) {
            if (root == nullptr) {
                root = nodes_degree_list[i];
                root->left = nodes_degree_list[i];
                root->right = nodes_degree_list[i];
            } else {
                insert(root, nodes_degree_list[i]);
                if (nodes_degree_list[i]->key < root->key) {
                    root = nodes_degree_list[i];
                }
            }
        }
    }
    delete[] nodes_degree_list;
}

template<typename I, typename K>
Fibnode <I, K> *Fibheap<I, K>::merge(Fibnode <I, K> *parent, Fibnode <I, K> *child) {
    child->right->left = child->left;
    child->left->right = child->right;
    if (parent->child == nullptr) {
        parent->child = child;
        child->left = child;
        child->right = child;
    } else {
        insert(parent->child, child);
    }
    child->parent = parent;
    child->marked = false;
    return parent;
}

template<typename I, typename K>
void Fibheap<I, K>::insert(Fibnode <I, K> *parent, Fibnode <I, K> *child) {
    parent->left->right = child;
    child->left = parent->left;
    parent->left = child;
    child->right = parent;
}

template<typename I, typename K>
void Fibheap<I, K>::cut(Fibnode <I, K> *parent, Fibnode <I, K> *child) {
    if (child->left == child) {
        parent->child = nullptr;
    } else {
        child->right->left = child->left;
        child->left->right = child->right;
        if (parent->child == child) {
            parent->child = child->left;
        }
    }
    parent->degree--;

    insert(root, child);
    child->parent = nullptr;
    child->marked = false;
}

template<typename I, typename K>
void Fibheap<I, K>::cascading_cut(Fibnode <I, K> *node) {
    Fibnode <I, K> *parent = node->parent;
    if (parent != nullptr) {
        if (node->marked) {
            cut(parent, node);
            cascading_cut(parent);
        } else {
            node->marked = true;
        }
    }
}