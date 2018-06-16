#include <map>
#include <memory>

#include "heap.hpp"

template<typename I, typename K>
class Dijkstra {
public:
    Dijkstra(const std::unordered_map <I, std::unordered_map<I, K>> &graph, std::unique_ptr <Heap<I, K>> h, I start);
};

#include "dijkstra.tpp"