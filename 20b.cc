#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

const vector<pint> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main()
{
    const int MINSAVE = 100;
    ifstream file("20.input");
    string s;
    vector<string> racetrack;
    while (getline(file, s)) racetrack.push_back(s);

    int n = racetrack.size();
    int m = racetrack[0].size();
    pint startPos, endPos;

    vector<vector<int>> dist (n, vector<int> (m, __INT_MAX__));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (racetrack[i][j] == 'S')
            {
                startPos = {i, j};
                dist[i][j] = 0;
            }
            else if (racetrack[i][j] == 'E') endPos = {i, j};
        }
    }
    

    queue<pint> q;
    q.push(startPos);
    while (!q.empty())
    {
        pint pos = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            pint dir = DIRS[d];
            pint next = {pos.x + dir.x, pos.y + dir.y};

            if (racetrack[next.x][next.y] != '#' and dist[next.x][next.y] > dist[pos.x][pos.y] + 1)
            {
                dist[next.x][next.y] = dist[pos.x][pos.y] + 1;
                q.push(next);
            }
        }
    }

    int goodCheats = 0;

    for (int i1 = 1; i1 < n - 1; i1++)
    {
        for (int j1 = 1; j1 < m - 1; j1++)
        {
            if (racetrack[i1][j1] == '#') continue;
            for (int i2 = max(1, i1 - 20); i2 < min(n - 1, i1 + 21); i2++)
            {
                for (int j2 = max(1, j1 - 20); j2 < min(m - 1, j1 + 21); j2++)
                {
                    int manhattan = abs(i1 - i2) + abs(j1 - j2);
                    if (racetrack[i2][j2] == '#' or manhattan > 20) continue;
                    if (abs(dist[i1][j1] - dist[i2][j2]) - manhattan >= MINSAVE)
                        goodCheats++;
                }
            }
        }
    }
    cout << goodCheats / 2 << endl;
}