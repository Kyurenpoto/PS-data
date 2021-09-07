#include <algorithm>
#include <array>
#include <numeric>
#include <unordered_map>

struct InternalGraphEdge
{
    int from;
    int to;
};

template<size_t V, size_t E>
struct Edges
{
    std::array<InternalGraphEdge, E> edge;
    std::array<int, V> begin, end;

    void init(int edgeNum)
    {
        std::sort(edge.begin(), edge.begin() + edgeNum,
            [](const InternalGraphEdge& a, const InternalGraphEdge& b)
            {
                return a.from < b.from || (a.from == b.from && a.to < b.to);
            }
        );

        std::fill(begin.begin(), begin.end(), E);
        std::fill(end.begin(), end.end(), 0);

        for (int i = 0; i < edgeNum; ++i)
        {
            begin[edge[i].from] = std::min(begin[edge[i].from], i);
            end[edge[i].from] = std::max(end[edge[i].from], i);
        }
    }
};

struct ExternalGraphEdge
{
    int from;
    int to;
};

struct VertexConverter
{
    virtual int toInternal(int ex) = 0;

    virtual int toExternal(int ex) = 0;
};

struct EdgeConverter
{
    InternalGraphEdge toInternal(const ExternalGraphEdge& ex, VertexConverter& vertexConverter) const
    {
        InternalGraphEdge in;
        in.from = vertexConverter.toInternal(ex.from);
        in.to = vertexConverter.toInternal(ex.to);

        return in;
    }

    ExternalGraphEdge toExternal(const InternalGraphEdge& in, VertexConverter& vertexConverter) const
    {
        ExternalGraphEdge ex;
        ex.from = vertexConverter.toExternal(in.from);
        ex.to = vertexConverter.toExternal(in.to);

        return ex;
    }
};

template<int MinVertexId>
struct MinVertexIdVertexConverter :
    VertexConverter
{
    int toInternal(int ex) final
    {
        return ex - MinVertexId;
    }

    int toExternal(int in) final
    {
        return in + MinVertexId;
    }
};

struct ArrangedVertexConverter :
    VertexConverter
{
    std::unordered_map<int, int> arranged, inverse;

    int toInternal(int ex) final
    {
        return arranged[ex];
    }

    int toExternal(int in) final
    {
        return inverse[in];
    }

    void addArrangePair(int from, int to)
    {
        arranged[from] = to;
        inverse[to] = from;
    }
};

template<size_t V>
struct Vertice
{
    std::array<int, V> vertex;
};
