#include <limits>

template <template <typename, typename> typename H, typename I, typename K>
Dijkstra<H, I, K>::Dijkstra(const std::map<I, std::map<I, K>> &graph, I start, K max)
{
    std::map<I, K> distances;
    for (auto i : graph)
    {
        distances[i.first] = max;
    }
    distances[start] = 0;
    heap = H<I, K>();
}