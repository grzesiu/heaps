#include <iostream>
#include <limits>
#include <set>

template<template<typename, typename> typename H, typename I, typename K>
Dijkstra<H, I, K>::Dijkstra(const std::unordered_map <I, std::unordered_map<I, K>> &graph,
                            H<I, K> h, I start, K min, K max): h(h) {
    std::set <I> ids;
    for (auto nodes_map: graph) {
        for (auto node : nodes_map.second) {
            ids.insert(node.first);
        }
    }
    ids.erase(start);
    h.create(ids, max);

    I current = start;

    std::map <I, K> distances;
    distances[start] = min;

    while (!h.empty()) {
        for (auto node : graph.at(current)) {
            if (!distances.count(node.first)) {
                h.increase_priority(node.first, distances[current] + node.second);
            }
        }
        current = h.top().first;
        distances[current] = h.top().second;
        std::cout << current << " " << distances[current] << std::endl;
        h.pop();
    }
}