#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define int long long
using namespace std;

vector<string> towels;
vector<int> posCache;

int possible(const string& design, int l)
{
    if (posCache[l] != -1) return posCache[l];

    int n = design.size();

    int possibilities = 0;
    for (string towel : towels)
    {
        //cout << "Trying to use " << towel << " for " << design << " at pos " << l << endl;
        int towelSize = towel.size();
        if (l + towelSize > n) continue;

        bool goodTowel = true;
        for (int i = l; i < l + towelSize and goodTowel; i++)
        {
            goodTowel = design[i] == towel[i - l];
        }
        if (goodTowel) possibilities += possible(design, l + towelSize);
    }
    posCache[l] = possibilities;
    return possibilities;
}

vector<string> readStringsFromLine(string& s)
{
    vector<string> v (1, "");
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        if (s[i] == ',')
        {
            v.push_back("");
            i++;
        }
        else v[v.size() - 1].push_back(s[i]);
    }

    return v;
}

signed main()
{
    ifstream file("19.input");
    string s, design;
    getline(file, s);
    towels = readStringsFromLine(s);
    getline(file, s);

    //sort(towels.begin(), towels.end());

    int total = 0;
    while (getline(file, design))
    {
        int n = design.size();
        posCache.resize(design.size() + 1);
        for (int i = 0; i < n; i++) posCache[i] = -1;
        posCache[design.size()] = 1;
        total += possible(design, 0);

        //for (int x : posCache) cout << x << ' ';
        //cout  << endl;
    }
    cout << total << endl;
}