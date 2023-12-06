#include <algorithm>
#include <array>
#include <iostream>
#include <mutex>
#include <string>
#include <execution>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;

uint32_t to_int(const string& str, uint32_t start, uint32_t end)
{
    uint32_t val = 0;
    for (size_t i = start; i < end; ++i)
    {
        val = val * 10 + (str[i] - '0');
    }
    return val;
}

uint32_t main()
{
    ifstream file("input.txt");

    vector<tuple<uint32_t, uint32_t>> seeds;
    array<vector<tuple<uint32_t, uint32_t, uint32_t>>, 7> maps;

    string str;
    while (getline(file, str) && !str.empty())
    {
        size_t seedStart = str.find(':');
        seedStart = seedStart > str.length() ? 0 : seedStart + 2;
        uint32_t seedEnd = 0;
        while (seedEnd < str.length())
        {
            seedEnd = str.find(' ', seedStart);
            uint32_t seed = to_int(str, seedStart, seedEnd);
            seedStart = seedEnd + 1;
            seedEnd = str.find(' ', seedStart);
            seedEnd = seedEnd > str.length() ? str.length() : seedEnd;
            uint32_t range = to_int(str, seedStart, seedEnd);
            seeds.emplace_back(make_tuple(seed, range));
            seedStart = seedEnd + 1;
        }
    }

    getline(file, str);

    uint32_t idx = 0;
    while (getline(file, str))
    {
        auto& currentMap = maps[idx];
        if (str[0] >= '0' && str[0] <= '9')
        {
            size_t offset1 = str.find(' ', 0);
            uint32_t val1 = to_int(str, 0, offset1);
            size_t offset2 = str.find(' ', offset1 + 1);
            uint32_t val2 = to_int(str, offset1 + 1, offset2);
            uint32_t val3 = to_int(str, offset2 + 1, str.size());

            currentMap.emplace_back(make_tuple(val1, val2, val3));
        }
        else if (str.empty())
        {
            idx++;
        }
    }

    // I know there's a better way but it was too late when I realized :)
    std::mutex m;
    uint32_t minLocation = UINT32_MAX;
    for_each(execution::par, begin(seeds), end(seeds), [&](const auto& seed)
    {   
        uint32_t seedMin = UINT32_MAX;
        for (size_t i = 0; i < get<1>(seed); i++)
        {
            uint32_t mapIdx = get<0>(seed) + i;
            for (const auto& map : maps)
            {
                for (const auto& tuple : map)
                {
                    if (get<1>(tuple) <= mapIdx && mapIdx < get<1>(tuple) + get<2>(tuple))
                    {
                        mapIdx = get<0>(tuple) + (mapIdx - get<1>(tuple));
                        break;
                    }
                }
            }
            seedMin = min(seedMin, mapIdx);
        }
        m.lock();
        minLocation = min(minLocation, seedMin);
        m.unlock();
    });

    cout << minLocation << endl;
}
