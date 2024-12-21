#include <iostream>
#include <vector>
#include <fstream>
#define x first
#define y second
using namespace std;

pair<int, int> calcAntinode(pair<int, int> a, pair<int, int> b)
{
    return {2 * a.x - b.x, 2 * a.y -  b.y};
}

int main()
{
    ifstream file("8.input");
    string s;
    vector<vector<pair<int, int>>> antennas ('z' - '0' + 1);
    int n = 0, m;
    while (getline(file, s))
    {   
        m = s.size();
        for (int j = 0; j < m; j++) antennas[s[j] - '0'].push_back({n, j});
        n++;
    }

    //cout << n << ' ' << m << endl;

    int totalAntinodes = 0;
    vector<vector<bool>> antinodes (n, vector<bool> (m, false));

    for (vector<pair<int, int>> v : antennas)
    {
        int a = v.size();
        for (int i = 0; i < a; i++)
        {
            for (int j = i + 1; j < a; j++)
            {
                pair<int, int> anti1 = calcAntinode(v[i], v[j]);
                pair<int, int> anti2 = calcAntinode(v[j], v[i]);

                //cout << "Checking " << anti1.x << ' ' << anti1.y << " and " << anti2.x << ' ' << anti2.y << endl;

                if (0 <= anti1.x and anti1.x < n and 0 <= anti1.y and anti1.y < m and !antinodes[anti1.x][anti1.y])
                {
                    totalAntinodes++;
                    antinodes[anti1.x][anti1.y] = true;
                }

                if (0 <= anti2.x and anti2.x < n and 0 <= anti2.y and anti2.y < m and !antinodes[anti2.x][anti2.y])
                {
                    totalAntinodes++;
                    antinodes[anti2.x][anti2.y] = true;
                }
            }
        }
    }

    cout << totalAntinodes << endl;
}