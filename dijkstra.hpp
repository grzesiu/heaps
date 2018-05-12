#include <map>

template<template<typename, typename> typename H, typename I, typename K>
class Dijkstra {
public:
    Dijkstra(const std::unordered_map <I, std::unordered_map<I, K>> &graph, H<I, K> h, I start, K min, K max);

private:
    H<I, K> h;
};

#include "dijkstra.tpp"