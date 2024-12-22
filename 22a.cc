#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

signed main()
{
    ifstream file("22.input");
    string s;
    int out = 0;
    const int M = 16777216 - 1;
    while (getline(file, s))
    {
        int n = stoi(s);
        for (int i = 0; i < 2000; i++)
        {
            n ^= n << 6;
            n &= M;
            //n ^= n >> 5;
            //n ^= n << 11;

            n = n ^ (n >> 5) ^ ((n ^ (n >> 5)) << 11);
            //n = n ^ (n >> 5) ^ ((n << 11) ^ (n << 6)); <-- wrong

            n &= M;
        }
        cout << n << endl;
        out += n;
    }
    cout << out << endl;
}