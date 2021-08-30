#include <array>
#include <algorithm>
#include <vector>

struct ZArray
{
    const std::string origin;
    std::vector<int> arr;

    ZArray(const std::string& origin) :
        origin(origin)
    {
        int n = origin.length();
        std::fill_n(arr.begin(), n, 0);

        for (int i = 1, l = 0, r = 0; i < n; ++i)
        {
            if (i <= r)
                arr[i] = std::min(r - i + 1, arr[i - l]);
            
            while (i + arr[i] < n && origin[i + arr[i]] == origin[arr[i]])
                ++arr[i];
            
            if (r < i + arr[i] - 1)
            {
                r = i + arr[i] - 1;
                l = i;
            }
        }
    }
};
