#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#define int long long

void readNumbersFromLine(const string& s, vector<int>& v, int& r)
{
    r = 0;
    int n = s.size();
    bool reading_v = false;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == ':') reading_v = true;
        else if (s[i] == ' ') v.push_back(0);
        else if (reading_v) v[v.size() - 1] = v[v.size() - 1] * 10 + (s[i] - '0');
        else r = r * 10 + (s[i] - '0');
    }
}

signed main()
{
    ifstream file("7.input");
    string s;

    int out = 0;

    while (getline(file, s))
    {
        int r;
        vector<int> v (0);
        readNumbersFromLine(s, v, r);
        
        const int COMBS = (1 << (v.size() - 1));

        for (int c = 0; c < COMBS; c++)
        {
            int result = v[0];
            for (int i = 1; i < v.size(); i++)
            {
                if (c & (1 << (i - 1))) result *= v[i];
                else result += v[i];
            }
            if (result == r)
            {
                out += r;
                break;
            }
        }
    }

    cout << out << endl;
}