#include "suffix_array.h"

struct LongestCommonPrefix
{
    const std::string& origin;
    const std::vector<int> arr;

    LongestCommonPrefix(const std::string& origin, const std::vector<int>& arr) :
        origin(origin),
        arr(arr)
    {}
};

struct LongestCommonPrefixFactory
{
    const std::string& origin;

    LongestCommonPrefixFactory(const std::string& origin) :
        origin(origin)
    {}

    LongestCommonPrefix create()
    {
        const int n = origin.size();
        std::vector<int> arr(n);
        std::vector<int> inverseSuffixArray(n);
        SuffixArray suffixArray(SuffixArrayFactory(origin).create());

        for (int i = 0; i < n; ++i)
            inverseSuffixArray[suffixArray.arr[i]] = i;

        for (int i = 0, k = 0; i < n; ++i)
            if (inverseSuffixArray[i] > 0)
            {
                for (; suffixArray.arr[inverseSuffixArray[i] - 1] + k < n &&
                    origin[i + k] == origin[suffixArray.arr[inverseSuffixArray[i] - 1] + k];
                    ++k);
                
                arr[inverseSuffixArray[i]] = k;
                k = std::max(0, k - 1);
            }

        return LongestCommonPrefix(origin, arr);
    }
};
