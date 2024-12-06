#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Pos
{
    int x, y;
};

int n, m;
const vector<Pos> DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const vector<int> POW = {1, 10, 100, 1000};

int timeLoop(const vector<string>& map, Pos pos, Pos obs)
{
    int dir = 0;
    vector<vector<int>> visited (n, vector<int> (m, 0));

    while (0 <= pos.x and pos.x < n and 0 <= pos.y and pos.y < m)
    {
        if (visited[pos.x][pos.y] / POW[dir] % 10 == 1)
        {
            return 1;
        }
        visited[pos.x][pos.y] += POW[dir];

        int newx = pos.x + DIRS[dir].x;
        int newy = pos.y + DIRS[dir].y;

        if (0 <= newx and newx < n and 0 <= newy and newy < m and (map[newx][newy] == '#' or (newx == obs.x and newy == obs.y)))
        {
            dir = (dir + 1) % 4;
        }
        else pos = {newx, newy};
    }
    return 0;
}

int main()
{
    ifstream file("6.input");
    string s;

    vector<string> map;
    while (getline(file, s)) map.push_back(s);

    n = map.size();
    m = map[0].size();

    Pos startingPos;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == '^')
                startingPos = {i, j};

    int timeLoops = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] != '#')
                timeLoops += timeLoop(map, startingPos, {i, j});
    
    cout << timeLoops << endl;
}