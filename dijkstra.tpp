#include <iostream>
#include <limits>
#include <set>

template<typename I, typename K>
Dijkstra<I, K>::Dijkstra(const std::unordered_map <I, std::unordered_map<I, K>> &graph,
                         std::unique_ptr <Heap<I, K>> h, I start) {
    std::set <I> ids;
    for (auto nodes_map: graph) {
        ids.insert(nodes_map.first);
        for (auto node : nodes_map.second) {
            ids.insert(node.first);
        }
    }
    ids.erase(start);
    h->create(ids, std::numeric_limits<K>::max());

    I current = start;

    std::map <I, K> distances;
    distances[start] = 0;
    std::cout << start << std::endl;
    while (!h->empty()) {
        for (auto node : graph.at(current)) {
            if (!distances.count(node.first) && distances[current] != std::numeric_limits<K>::max()) {
                h->increase_priority(node.first, distances[current] + node.second);
            }
        }
        current = h->top().first;
        distances[current] = h->top().second;
        std::cout << current << " " << distances[current] << std::endl;
        h->pop();
    }
}