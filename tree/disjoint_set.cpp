#include <array>
#include <algorithm>
#include <numeric>

template<size_t N>
struct DisjointSet
{
    std::array<int, N> parent;
    std::array<int, N> size;

    DisjointSet()
    {
        std::iota(parent, parent + N, 0);
        std::iota(size, size + N, 0);
    }

    void unionTrees(int a, int b)
    {
        a = find(a);
        b = find(b);
        
        if (size[a] < size[b])
            mergeTrees(b, a);
        else
            mergeTrees(a, b);
    }

    void mergeTrees(int from, int to)
    {
        parent[to] = from;
        size[to] += size[from];
    }

    int findRoot(int a)
    {
        if (parent[a] == a)
            return a;
        else
            return (parent[a] = findRoot(parent[a]));
    }
};
