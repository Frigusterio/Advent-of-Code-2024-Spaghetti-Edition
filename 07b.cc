#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
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
        
        const int COMBS = pow(3, v.size() - 1);

        for (int c = 0; c < COMBS; c++)
        {
            int result = v[0];
            for (int i = 1; i < v.size(); i++)
            {
                int d = c / signed(pow(3, (i - 1))) % 3;
                if (d == 0) result *= v[i];
                else if (d == 1) result += v[i];
                else result = result * pow(10, digits(v[i])) + v[i];

                if (result > r) break;
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