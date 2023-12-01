#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream file("input.txt");

    vector<string> numbers{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    uint32_t sum = 0;
    string str;
    while (getline(file, str))
    {
        int32_t first = -1;
        int32_t last = -1;
        for (size_t i = 0; i < str.length(); ++i)
        {
            for (size_t e = 1; e < 10; ++e)
            {
                const string& number = numbers[e - 1];
                if (str.compare(i, number.length(), number) == 0 || e + '0' == str[i])
                {
                    if (first == -1)
                        first = e;

                    last = e;
                }
            }
        }
        sum += first * 10 + last;
    }

    cout << sum << endl;
}