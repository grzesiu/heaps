#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <map>


template<typename I, typename K>
class Node {
public:
    Node(I id, K key);

    I get_id() const;

    K get_key() const;

protected:
    I id;
    K key;
};

template<typename I, typename K>
Node<I, K>::Node(I id, K key) : id(id), key(key) {}

template<typename I, typename K>
I Node<I, K>::get_id() const {
    return id;
}

template<typename I, typename K>
K Node<I, K>::get_key() const {
    return key;
}

template<typename I, typename K>
class Heap {
public:
    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual std::pair <I, K> top() const = 0;

    virtual void create(const std::set <I> &ids, K max) = 0;

    virtual void push(I id, K key) = 0;

    virtual void pop() = 0;

    virtual void increase_priority(I id, K key) = 0;

    virtual void erase(I id) = 0;
};

template<typename I, typename K>
class Darynode : public Node<I, K> {
    template<typename, typename>
    friend
    class Daryheap;

public:
    Darynode(I id, K key);
};

template<typename I, typename K>
Darynode<I, K>::Darynode(I id, K key) : Node<I, K>::Node(id, key) {}

template<typename I, typename K>
class Daryheap : public Heap<I, K> {
public:
    Daryheap(int d);

    bool empty() const;

    int size() const;

    std::pair <I, K> top() const;

    void create(const std::set <I> &ids, K max);

    void push(I id, K key);

    void pop();

    void increase_priority(I id, K key);

    void erase(I id);

private:
    int d;
    std::map<I, int> indices;
    std::vector <Darynode<I, K>> nodes;

    void heapify(int i);

    int parent_index(int i);

    int left_index(int i);

    int right_index(int i);

    void swap(int i, int j);
};


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
        indices[id] = nodes.size();
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

template<typename I, typename K>
class Fibnode : public Node<I, K> {
    template<typename, typename>
    friend
    class Fibheap;

public:
    Fibnode(I id, K key);

    bool is_marked() const;

private:
    bool marked = false;
    int degree = 0;
    Fibnode *parent = nullptr;
    Fibnode *left = nullptr;
    Fibnode *right = nullptr;
    Fibnode *child = nullptr;
};

template<typename I, typename K>
Fibnode<I, K>::Fibnode(I id, K key) : Node<I, K>::Node(id, key) {}

template<typename I, typename K>
bool Fibnode<I, K>::is_marked() const {
    return this->marked;
}

template<typename I, typename K>
class Fibheap : public Heap<I, K> {
public:
    Fibheap();

    ~Fibheap();

    bool empty() const;

    int size() const;

    std::pair <I, K> top() const;

    void create(const std::set <I> &ids, K max);

    void push(I id, K key);

    void pop();

    void increase_priority(I id, K key);

    void erase(I id);

private:
    std::map<I, Fibnode<I, K> *> nodes;
    Fibnode<I, K> *root;

    int get_max_degree() const;

    void consolidate();

    Fibnode<I, K> *merge(Fibnode<I, K> *parent, Fibnode<I, K> *child);

    void insert(Fibnode<I, K> *parent, Fibnode<I, K> *child);

    void cut(Fibnode<I, K> *parent, Fibnode<I, K> *child);

    void cascading_cut(Fibnode<I, K> *node);
};

template<typename I, typename K>
Fibheap<I, K>::Fibheap() : root(nullptr) {}

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
    Fibnode<I, K> *node = new Fibnode<I, K>(id, key);
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
        Fibnode<I, K> *curr = root->child;
        if (curr != nullptr) {
            Fibnode<I, K> **children = new Fibnode<I, K> *[root->degree]();
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

        Fibnode<I, K> *old_root = root;

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
    Fibnode<I, K> *node = nodes[id];
    if (key < node->key) {
        node->key = key;
        Fibnode<I, K> *parent = node->parent;
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
    Fibnode<I, K> **nodes_degree_list = new Fibnode<I, K> *[max_degree]();
    Fibnode<I, K> *curr = root;
    int root_list_size = 0;

    do {
        root_list_size++;
        curr = curr->left;
    } while (curr != root);

    Fibnode<I, K> **root_list = new Fibnode<I, K> *[root_list_size];

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
Fibnode<I, K> *Fibheap<I, K>::merge(Fibnode<I, K> *parent, Fibnode<I, K> *child) {
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
void Fibheap<I, K>::insert(Fibnode<I, K> *parent, Fibnode<I, K> *child) {
    parent->left->right = child;
    child->left = parent->left;
    parent->left = child;
    child->right = parent;
}

template<typename I, typename K>
void Fibheap<I, K>::cut(Fibnode<I, K> *parent, Fibnode<I, K> *child) {
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
void Fibheap<I, K>::cascading_cut(Fibnode<I, K> *node) {
    Fibnode<I, K> *parent = node->parent;
    if (parent != nullptr) {
        if (node->marked) {
            cut(parent, node);
            cascading_cut(parent);
        } else {
            node->marked = true;
        }
    }
}

std::map<int, int> dijkstra(const std::unordered_map<int, std::unordered_map<int, int>> &graph, int current) {

    Fibheap<int, int> h;

    std::set<int> ids;
    for (auto nodes_map: graph) {
        ids.insert(nodes_map.first);
    }

    ids.erase(current);
    h.create(ids, std::numeric_limits<int>::max());

    std::map<int, int> distances;
    distances[current] = 0;

    while (!h.empty()) {
        for (auto node : graph.at(current)) {
            if (!distances.count(node.first) && distances.at(current) != std::numeric_limits<int>::max()) {
                h.increase_priority(node.first, distances.at(current) + node.second);
            }
        }
        current = h.top().first;
        distances[current] = h.top().second;
        h.pop();
    }
    return distances;
}

std::vector <std::pair<int, int>>
generate_edges(int v) {
    int c = 0;
    std::vector <std::pair<int, int>> edges(v * (v - 1) / 2);
    for (int i = 0; i < v; ++i) {
        for (int j = i + 1; j < v; ++j) {
            edges[c] = std::make_pair(i, j);
            c++;
        }
    }
    return edges;
}


std::unordered_map<int, std::unordered_map<int, int>>
generate_random_graph(int v, float density, std::vector <std::pair<int, int>> &edges, int max_distance) {

    std::mt19937 rng;
    rng.seed(std::random_device()());

    std::uniform_int_distribution <std::default_random_engine::result_type> distances(0, max_distance);
    std::unordered_map<int, std::unordered_map<int, int>> graph;
    std::shuffle(std::begin(edges), std::end(edges), rng);


    for (int i = 0; i < density * v * (v - 1) / 2; ++i) {
        int distance = distances(rng);
        graph[edges[i].first][edges[i].second] = distance;
        graph[edges[i].second][edges[i].first] = distance;
    }

    return graph;
}

void print(const std::unordered_map<int, std::unordered_map<int, int>> &graph) {
    for (auto i : graph) {
        std::cout << i.first << ": ";
        for (auto j : i.second) {
            std::cout << j.first << ":" << j.second << ", ";
        }
        std::cout << std::endl;
    }
}


void hackerrank() {
    int t, n, m, x, y, s, start;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        std::unordered_map<int, std::unordered_map<int, int>> graph;

        while (m--) {
            scanf("%d %d %d", &x, &y, &s);
            if (!graph[x].count(y) || graph[x][y] > s) {
                graph[x][y] = s;
                graph[y][x] = s;
            }
        }

        scanf("%d", &start);

        auto distances = dijkstra(graph, start);
        for (const auto &distance : distances) {
            if (distance.first != start and distance.second != std::numeric_limits<int>::max()) {
                printf("%d ", distance.second);
            } else if (distance.second == std::numeric_limits<int>::max()) {
                printf("-1 ");
            }
        }
        printf("\n");
    }
}

int main() {
    hackerrank();
    return 0;
}