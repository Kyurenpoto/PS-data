#include <algorithm>
#include <array>
#include <numeric>

template<size_t N>
struct DisjointSet
{
    std::array<int, N> parent;
    std::array<int, N> size;

    DisjointSet()
    {
        std::iota(parent.begin(), parent.end(), 0);
        std::fill(size.begin(), size.end(), 1);
    }

    void unionTrees(int a, int b)
    {
        a = findRoot(a);
        b = findRoot(b);
        
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
