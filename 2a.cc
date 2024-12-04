#include <iostream>
#include <vector>
#include <fstream>
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

int main()
{
    ifstream file("2.input");
    string s;

    int safeReports = 0;

    while (getline(file, s))
    {
        vector<int> v = readNumbersFromLine(s);

        if (v.size() == 1)
        {
            safeReports++;
            continue;
        }

        if (v[0] == v[1] or abs(v[1] - v[0]) > 3) continue;

        bool safe = true, increasing = v[1] > v[0];
        int i = 2, n = v.size();
        while (i < n and safe)
        {
            safe = abs(v[i] - v[i - 1]) <= 3
                   and ((v[i] > v[i - 1] and increasing)
                   or (v[i] < v[i - 1] and !increasing));
            i++;
        }

        if (safe) safeReports++;
    }
    cout << safeReports << endl;
}