#include <iostream>
#include <map>
#include <random>
#include <utility>

#include "dijkstra.hpp"
#include "fibheap.hpp"

std::map<int, std::map<int, int>> generate_random_graph(int v, int e, int max_distance, bool undirected)
{
    if (undirected)
    {
        e /= 2;
    }
    std::map<int, std::map<int, int>> graph;
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> indices(0, v - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distances(0, max_distance);

    int c = 0;
    while (c < e)
    {
        int i = indices(rng);
        int j = indices(rng);

        if (i != j)
        {
            int d = distances(rng);

            int s = graph[i].size();
            graph[i][j] = d;
            if (undirected)
            {
                graph[j][i] = d;
            }
            if (s != graph[i].size())
            {
                c++;
            }
        }
    }

    return graph;
}

void print(const std::map<int, std::map<int, int>> &graph)
{
    for (auto i : graph)
    {
        std::cout << i.first << ": ";
        for (auto j : i.second)
        {
            std::cout << j.first << ":" << j.second << ", ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int v = 10;
    int e = 20;
    int d = 100;
    std::map<int, std::map<int, int>> graph = generate_random_graph(v, e, d, true);
    Dijkstra<Fibheap, int, int> dijkstra(graph, 0, std::numeric_limits<int>::max());
    return 0;
}