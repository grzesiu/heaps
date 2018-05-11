#include <map>

template<template<typename, typename> typename H, typename I, typename K>
class Dijkstra {
public:
    Dijkstra(const std::map <I, std::map<I, K>> &graph, H<I, K> h, I start, K max);

private:
    H<I, K> h;
};

#include "dijkstra.tpp"