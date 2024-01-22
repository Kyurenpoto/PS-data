#include "graph_base.h"

template<size_t V>
struct VerticeTopologicalSorter
{
    std::array<int, V> inDegree;

    template<size_t E>
    void sort(int vertexNum, Vertice<V>& destination, const Edges<V, E>& edge)
    {
        std::fill(inDegree.begin(), inDegree.end(), 0);

        for (int i = 0; i < vertexNum; ++i)
            for (int j = edge.begin[i]; j <= edge.end[i]; ++j)
                ++inDegree[edge.edge[j].to];

        int back = 0;
        for (int i = 0; i < vertexNum; ++i)
            if (inDegree[i] == 0)
                destination.vertex[back++] = i;

        for (int front = 0; front < vertexNum; ++front)
        {
            int vertex = destination.vertex[front];
            for (int i = edge.begin[vertex]; i <= edge.end[vertex]; ++i)
                if (--inDegree[edge.edge[i].to] == 0)
                    destination.vertex[back++] = edge.edge[i].to;
        }
    }
};
