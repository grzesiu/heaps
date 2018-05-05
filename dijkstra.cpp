#include <iostream>
#include <vector>
#include <set>
#include <random>

std::vector<std::set<int>> generate_random_graph(int v, int e, bool undirected)
{
    if (undirected)
    {
        e /= 2;
    }
    std::vector<std::set<int>> graph(v);
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, v - 1);

    int c = 0;
    while (c < e)
    {
        int i = dist(rng);
        int j = dist(rng);
        int s = graph[i].size();
        graph[i].insert(j);

        if (s != graph[i].size())
        {
            c++;
            if (undirected)
            {
                graph[j].insert(i);
            }
        }
    }

    return graph;
}

int main()
{
    int v = 10;
    int e = 20;
    std::vector<std::set<int>> graph = generate_random_graph(v, e, true);

    for (auto i : graph)
    {
        for (auto j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}