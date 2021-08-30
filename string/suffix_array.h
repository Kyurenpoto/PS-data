#include <algorithm>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

struct SuffixArray
{
    const std::string origin;
    std::vector<int> arr;

    struct CountingSorter
    {
        std::vector<int> count;

        CountingSorter(int n) :
            count(n)
        {}

        template<class Indexer>
        void sort(
            std::vector<int>::iterator begin,
            std::vector<int>::iterator end,
            std::vector<int>& index,
            Indexer indexer
        )
        {
            std::fill(count.begin(), count.end(), 0);
            
            int n = end - begin;
            for (int i = 0; i < n; ++i)
                ++count[*(begin + i)];

            for (int i = 1; i < count.size(); ++i)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; --1)
                index[--count[*(begin + i)] = indexer(i);
        }
    };

    SuffixArray(const std::string& origin) :
        origin(origin)
    {
        const int n = origin.length();
        std::vector<int> rank(n * 2), nextRank(n * 2), index(n);
        CountingSorter sorter(std::max(std::numeric_limits<char>::max(), n) + 1);

        arr.resize(n);
        std::iota(arr.begin(), arr.end(), 0);
        rank.insert(rank.begin(), origin.begin(), origin.end());

        for (int d = 1; d < n && rank[arr[n - 1]] != n; d *= 2)
        {
            sorter.sort(rank.begin + d, rank.begin + (n + d), index,[](int i) { return i; });
            sorter.sort(rank.begin, rank.begin + n, arr,[&index](int i) { return index[i]; });

            nextRank[arr[0]] = 1;

            auto cmp = [&d](int i, int j)
            {
                return rank[i] == rank[j] ? rank[i + d] < rank[j + d] : rank[i] < rank[j];
            };
            for (int i = 1; i < n; ++i)
                nextRank[arr[i]] =
                nextRank[arr[i - 1]] + (cmp(arr[i - 1], arr[i]) ? 1 : 0);

            std::copy_n(nextRank.begin(), n, rank.begin);
        }
    }
};