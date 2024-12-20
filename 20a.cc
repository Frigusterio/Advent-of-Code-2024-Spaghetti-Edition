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

    const int MINSAVE = 100;
    int goodCheats = 0;

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (racetrack[i][j] != '#') continue;
            if (racetrack[i - 1][j] != '#' and racetrack[i + 1][j] != '#' and abs(dist[i - 1][j] - dist[i + 1][j]) - 2 >= MINSAVE)
                goodCheats++;
            if (racetrack[i][j - 1] != '#' and racetrack[i][j + 1] != '#' and abs(dist[i][j - 1] - dist[i][j + 1]) - 2 >= MINSAVE)
                goodCheats++;
        }
    }
    cout << goodCheats << endl;
}