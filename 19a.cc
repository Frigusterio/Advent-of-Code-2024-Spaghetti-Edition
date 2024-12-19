#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<string> towels;

bool possible(const string& design, int l)
{
    int n = design.size();

    if (l == n) return true;

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
        if (goodTowel and possible(design, l + towelSize)) return true;
    }
    return false;
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

int main()
{
    ifstream file("19.input");
    string s, design;
    getline(file, s);
    towels = readStringsFromLine(s);
    getline(file, s);

    sort(towels.begin(), towels.end());

    int total = 0;
    while (getline(file, design)) total += possible(design, 0);
    cout << total << endl;
}