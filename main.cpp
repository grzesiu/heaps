#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>

#include "fibheap.hpp"
#include "daryheap.hpp"
#include "dijkstra.hpp"


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

int main() {

    int v = 10;
    int max_distance = 100;
    float density = 1.0;

    auto edges = generate_edges(v);
    auto graph = generate_random_graph(v, density, edges, max_distance);
    print(graph);
    Dijkstra<int, int> dijkstra(graph, std::make_unique<Daryheap<int, int>>(Daryheap<int, int>(2)),
                                graph.begin()->first);
    return 0;
}