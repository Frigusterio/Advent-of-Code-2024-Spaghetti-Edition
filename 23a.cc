#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<vector<int>> g (26 * 26);

int pctoi(char pc0, char pc1)
{
    return (pc0 - 'a') * 26 + (pc1 - 'a');
}

int dfs(int a, int start, int depth, bool t)
{
    if (depth == 3) return t and a == start;

    int out = 0;
    for (int x : g[a]) out += dfs(x, start, depth + 1, t or x / 26 == 't' - 'a');
    return out;
}

int main()
{
    ifstream file("23.input");
    string s;

    while (getline(file, s))
    {
        g[pctoi(s[0], s[1])].push_back(pctoi(s[3], s[4]));
        g[pctoi(s[3], s[4])].push_back(pctoi(s[0], s[1]));
    }

    int out = 0;
    for (int i = 0; i < 26 * 26; i++)
    {
        out += dfs(i, i, 0, i / 26 == 't' - 'a');
    }
    out /= 6;
    cout << out << endl;
}