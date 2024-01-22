#include <algorithm>
#include <array>

template <size_t N> struct LeastCommonAncestor {
    static constexpr int MAX_ANCESTOR = 30;
    std::array<std::array<int, MAX_ANCESTOR>, N> ancestor;

    LeastCommonAncestor(const std::array<int, N> &parent) {
        for (int i = 0; i < N; ++i) {
            std::fill(ancestor[i].begin(), ancestor[i].end(), i);

            ancestor[i][0] = parent[i];
        }

        for (int i = 1; i < MAX_ANCESTOR; ++i)
            for (int j = 0; j < N; ++j)
                ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
    }

    int rightMostBit(const int x) { return (x & (-x)); }

    int moveToAncestor(const int node, int diffDepth) {
        int moved = node;
        for (int i = 0; diffDepth > 0; ++i, diffDepth /= 2)
            if (diffDepth % 2 == 1)
                moved = ancestor[moved][i];

        return moved;
    }

    int leastCommonAncestor(int a, int b, const std::array<int, N> &depth) {
        if (depth[a] > depth[b])
            a = moveToAncestor(a, std::abs(depth[a] - depth[b]));
        else if (depth[a] < depth[b])
            b = moveToAncestor(b, std::abs(depth[a] - depth[b]));

        for (int i = MAX_ANCESTOR - 1; i >= 0 && a != b; --i) {
            if (ancestor[a][i] != ancestor[b][i]) {
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        }

        if (a != b) {
            a = ancestor[a][0];
            b = ancestor[b][0];
        }

        return a;
    }
};
