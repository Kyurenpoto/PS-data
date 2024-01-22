#include <algorithm>
#include <array>

template <size_t N, size_t SqrtN> struct Query {
    int idx, begin, end;
    bool operator<(const Query<N, SqrtN> &q) const {
        return begin / SqrtN == b.begin / SqrtN ? end < b.end : begin / SqrtN < b.begin / SqrtN;
    }
    virtual void operator()(const std::array<int, N> &table) = 0;
};

template <size_t N, size_t SqrtN, size_t Q> struct MoQueryProcesser {
    void exec(const std::array<int, N> &table, const std::array<Query<N, SqrtN>, Q> &query) {
        std::sort(query.begin(), query.end());
    }
};
