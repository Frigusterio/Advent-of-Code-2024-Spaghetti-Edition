#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <map>
#define int  __int128_t
using namespace std;

vector<int> readNumbersFromLine(string& s)
{
    vector<int> v (1, 0);
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ') v.push_back(0);
        else v[v.size() - 1] = v[v.size() - 1] * 10 + (s[i] - '0');
    }

    return v;
}

int digits(int n)
{
    int out = 0;
    while (n > 0)
    {
        n /= 10;
        out++;
    }
    return out;
}

map<pair<int, long long>, long long> blinkmap;

long long stones(int value, long long blinks)
{
    if (blinks ==  0) return 1;
    if (blinkmap.count({value, blinks})) return blinkmap[{value, blinks}];

    int s;
    if (value == 0) s = stones(1, blinks - 1);
    else
    {
        int d = digits(value);
        if (d % 2 == 0) s = stones(value / pow(10, d / 2), blinks - 1) + stones(value % int(pow(10, d / 2)), blinks - 1);
        else s = stones(value * 2024, blinks - 1);
    }

    blinkmap[{value, blinks}] = s;
    return s;
}

signed main()
{
    ifstream file("11.input");
    string s;
    getline(file, s);
    vector<int> v = readNumbersFromLine(s);

    int n = v.size();

    long long blinks;
    while (cin >> blinks)
    {
        long long out = 0;
        for (int i = 0; i < n; i++) out += stones(v[i], blinks);
        cout << out << endl;
    }
}