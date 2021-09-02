#include <algorithm>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

struct SuffixArray
{
    std::vector<int> arr;

    SuffixArray(const std::vector<int>& arr) :
        arr(arr)
    {}

    auto lowerbound(const std::string& origin, const std::string& pattern) const
    {
        return std::lower_bound(arr.begin(), arr.end(), pattern,
            [&origin](const int& idx, const std::string& x)
            {
                return origin.substr(idx, x.length()) < x;
            });
    }

    auto upperbound(const std::string& origin, const std::string& pattern) const
    {
        return std::upper_bound(arr.begin(), arr.end(), pattern,
            [&origin](const std::string& x, const int& idx)
            {
                return x < origin.substr(idx, x.length());
            });
    }
};

struct SuffixArrayFactory
{
    const std::string& origin;

    SuffixArrayFactory(const std::string& origin) :
        origin(origin)
    {}

    struct CountingSorter
    {
        std::vector<int> count;

        CountingSorter(size_t n) :
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

            size_t n = end - begin;
            for (int i = 0; i < n; ++i)
                ++count[*(begin + i)];

            for (int i = 1; i < count.size(); ++i)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; --i)
                index[--count[*(begin + indexer(i))]] = indexer(i);
        }
    };

    struct DoubleCountingSorter
    {
        std::vector<int> index;
        CountingSorter sorter;

        DoubleCountingSorter(size_t size) :
            index(size),
            sorter(std::max((size_t)std::numeric_limits<char>::max(), size) + 1)
        {}

        void sort(
            std::vector<int>& arr,
            std::vector<int>::iterator begin,
            std::vector<int>::iterator end,
            int d
        )
        {
            sorter.sort(begin + d, end + d, index, [](int i) { return i; });
            sorter.sort(begin, end, arr, [this](int i) { return index[i]; });
        }
    };

    struct SuffixRank
    {
        size_t meaningfulSize;
        std::vector<int> rank, nextRank;

        SuffixRank(size_t size) :
            meaningfulSize(size),
            rank(size * 2),
            nextRank(size * 2)
        {}

        void init(const std::string& origin)
        {
            std::copy(origin.begin(), origin.end(), rank.begin());
        }

        void update(const std::vector<int>& arr, size_t d)
        {
            nextRank[arr[0]] = 1;

            auto cmp = [&d, this](int i, int j)
            {
                return rank[i] == rank[j] ? rank[i + d] < rank[j + d] : rank[i] < rank[j];
            };
            for (int i = 1; i < meaningfulSize; ++i)
                nextRank[arr[i]] =
                nextRank[arr[i - 1]] + (cmp(arr[i - 1], arr[i]) ? 1 : 0);

            std::copy_n(nextRank.begin(), meaningfulSize, rank.begin());
        }

        std::vector<int>::iterator begin()
        {
            return rank.begin();
        }

        std::vector<int>::iterator end()
        {
            return rank.begin() + meaningfulSize;
        }

        bool updatable(const std::vector<int>& arr) const
        {
            return rank[arr[meaningfulSize - 1]] != meaningfulSize;
        }
    };

    SuffixArray create()
    {
        const size_t n = origin.length();
        std::vector<int> arr(n);
        DoubleCountingSorter sorter(n);
        SuffixRank rank(n);

        std::iota(arr.begin(), arr.end(), 0);
        rank.init(origin);

        for (size_t d = 1; d < n && rank.updatable(arr); d *= 2)
        {
            sorter.sort(arr, rank.begin(), rank.end(), d);

            rank.update(arr, d);
        }

        return SuffixArray(arr);
    }
};
