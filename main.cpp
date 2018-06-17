#include <algorithm>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>

#include "fibheap.hpp"
#include "daryheap.hpp"

template<typename T, typename std::enable_if<std::is_base_of<Heap<int, int>, T>::value>::type * = nullptr>
std::map<int, int> dijkstra(T h, const std::unordered_map<int, std::unordered_map<int, int>> &graph, int current) {

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

        printf("\n");

        auto distances = dijkstra(Daryheap<int, int>(2), graph, start);
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

void test_heap() {
    int t = 20;
    int v = 1000;
    int max_distance = 100;
    auto edges = generate_edges(v);

    while (t--) {
        for (float density = 0.1; density < 1.01; density += 0.1) {
            auto graph = generate_random_graph(v, density, edges, max_distance);

            std::clock_t begin = std::clock();

            dijkstra(Daryheap<int, int>(2), graph, graph.begin()->first);

            std::clock_t end = std::clock();
            std::cout << double(end - begin) / CLOCKS_PER_SEC;

            if (density < 0.99) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    test_heap();
    return 0;
}