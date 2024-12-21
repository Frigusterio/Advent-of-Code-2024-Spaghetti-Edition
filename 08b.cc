#include <iostream>
#include <vector>
#include <fstream>
#define x first
#define y second
using namespace std;

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
                pair<int, int> anti1 = v[i];
                pair<int, int> step1 = {v[i].x - v[j].x, v[i].y - v[j].y};

                while (0 <= anti1.x and anti1.x < n and 0 <= anti1.y and anti1.y < m)
                {
                    if (!antinodes[anti1.x][anti1.y])
                    {
                        totalAntinodes++;
                        antinodes[anti1.x][anti1.y] = true;
                    }
                    anti1 = {anti1.x + step1.x, anti1.y + step1.y};
                }

                pair<int, int> anti2 = v[j];
                pair<int, int> step2 = {v[j].x - v[i].x, v[j].y - v[i].y};

                while (0 <= anti2.x and anti2.x < n and 0 <= anti2.y and anti2.y < m)
                {
                    if (!antinodes[anti2.x][anti2.y])
                    {
                        totalAntinodes++;
                        antinodes[anti2.x][anti2.y] = true;
                    }
                    anti2 = {anti2.x + step2.x, anti2.y + step2.y};
                }
            }
        }
    }

    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << antinodes[i][j];
        }
        cout << endl;
    }*/

    cout << totalAntinodes << endl;
}