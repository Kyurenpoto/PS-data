#include <algorithm>
#include <string>
#include <vector>

struct Manacher
{
    const std::string& origin;
    const std::vector<int> arr;

    Manacher(const std::string& origin, const std::vector<int>& arr) :
        origin(origin),
        arr(arr)
    {}
};

struct ManacherFactory
{
    const std::string& origin;

    ManacherFactory(const std::string& origin) :
        origin(origin)
    {}

    Manacher create()
    {
        int n = origin.length();
        std::vector<int> arr(n);
        std::fill_n(arr.begin(), n, 0);

        for (int i = 0, k = -1, r = -1; i < n; ++i)
        {
            if (i <= r)
                arr[i] = std::min(r - i, arr[k * 2- i]);

            while (i - arr[i] - 1 >= 0 && i + arr[i]  + 1 < n && origin[i - arr[i] - 1] == origin[i + arr[i] + 1])
                ++arr[i];

            if (r < i + arr[i])
            {
                r = i + arr[i];
                k = i;
            }
        }

        return Manacher(origin, arr);
    }
};
