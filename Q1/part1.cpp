#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    ifstream file("input.txt");

    uint32_t sum = 0;
    string str;
    while (getline(file, str))
    {
        int32_t first = -1;
        int32_t last = -1;
        for (const char& c : str)
        {
            if (c >= '0' && c <= '9')
            {
                if (first == -1)
                    first = c - '0';

                last = c - '0';
            }
        }
        sum += first * 10 + last;
    }

    cout << sum << endl;
}