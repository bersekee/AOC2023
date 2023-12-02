#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    ifstream file("input.txt");

    array<uint32_t, 3> maxValues{ 12, 13, 14 };

    uint32_t sum = 0;
    uint32_t lineCount = 1;

    string str;
    while (getline(file, str))
    {
        bool isValid = true;
        size_t start = str.find(':') + 1;
        while (start < str.length())
        {
            size_t end = str.find(' ', start + 1);
            size_t count;
            from_chars(str.c_str() + start + 1, str.c_str() + end, count);
            const char& c = str[end + 1];
            uint32_t idx;
            if (c == 'r')
            {
                idx = 0;
            }
            else if (c == 'g')
            {
                idx = 1;
            }
            else
            {
                idx = 2;
            }
            if (count > maxValues[idx])
            {
                isValid = false;
                break;
            }
            start = str.find(' ', end + 1);
        }
        if (isValid)
        {
            sum += lineCount;
        }
        lineCount++;
    }

    cout << sum << endl;
}