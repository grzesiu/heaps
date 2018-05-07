#include <map>

template<template<typename, typename> typename H, typename I, typename K>
class Dijkstra {
public:
    Dijkstra(const std::map <I, std::map<I, K>> &graph, I start, K max);

private:
    H<I, K> heap;
};

#include "dijkstra.tpp"