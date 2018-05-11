#include <limits>
#include <set>

template<template<typename, typename> typename H, typename I, typename K>
Dijkstra<H, I, K>::Dijkstra(const std::map <I, std::map<I, K>> &graph, H<I, K> h, I start, K max) : h(h) {
    std::set <I> ids;
    for (auto nodes_map: graph) {
        for (auto node : nodes_map.second) {
            ids.insert(node.first);
        }
    }
    ids.erase(start);
    h.create(ids, max);
}