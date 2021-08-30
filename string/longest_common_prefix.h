#include "suffix_array.h"

struct LongestCommonPrefixArray
{
    SuffixArray suffixArray;
    std::vector<int> arr;

    LongestCommonPrefixArray(const std::string& origin) :
        suffixArray(origin)
    {
        const int n = origin.size();
        std::vector<int> inverseSuffixArray(n);

        for (int i = 0; i < n; ++i)
            inverseSuffixArray[suffixArray[i]] = i;

        for (int i = 0, k = 0; i < n; ++i)
            if (inverseSuffixArray[i] > 0)
            {
                for (; suffixArray[inverseSuffixArray[i] - 1] + k < n &&
                    origin[i + k] == origin[suffixArray[inverseSuffixArray[i] - 1] + k];
                    ++k);
                
                arr[inverseSuffixArray[i]] = k;
                k = std::max(0, k - 1);
            }
    }
};
