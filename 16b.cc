#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

const vector<pint> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

pint startPos, endPos;
vector<vector<bool>> visitedPositions;
int visited = 0;
vector<vector<vector<vector<pair<pint, int>>>>> parents;

void checkParent(pair<pint, int> pos)
{
    if (!visitedPositions[pos.first.x][pos.first.y])
    {
        visitedPositions[pos.first.x][pos.first.y] = true;
        visited++;
    }

    if (pos.first == startPos) return;

    for (pair<pint, int> parent : parents[pos.first.x][pos.first.y][pos.second])
    {
        checkParent(parent);
    }
}

int main()
{
    ifstream file("16.input");
    string s;
    vector<string> maze;
    while (getline(file, s)) maze.push_back(s);

    int n = maze.size();
    int m = maze[0].size();
    startPos = {n - 2, 1};
    endPos = {1, m - 2};

    queue<pair<pint, int>> q;
    vector<vector<vector<int>>> points (n, vector<vector<int>> (m, vector<int> (4, __INT_MAX__)));
    parents.resize(n, vector<vector<vector<pair<pint, int>>>> (m, vector<vector<pair<pint, int>>> (4, vector<pair<pint, int>> (0))));
    q.push({startPos, 1});
    points[startPos.x][startPos.y][1] = 0;

    while (!q.empty())
    {
        pint pos = q.front().first;
        int dir = q.front().second;
        q.pop();

        pint next = {pos.x + DIRS[dir].x, pos.y + DIRS[dir].y};

        if (maze[next.x][next.y] != '#')
        {
            if (points[next.x][next.y][dir] == points[pos.x][pos.y][dir] + 1)
                parents[next.x][next.y][dir].push_back({pos, dir});
            else if (points[next.x][next.y][dir] > points[pos.x][pos.y][dir] + 1)
            {
                points[next.x][next.y][dir] = points[pos.x][pos.y][dir] + 1;
                parents[next.x][next.y][dir] = {{pos, dir}};
                q.push({next, dir});
            }
        }

        if (points[pos.x][pos.y][(dir + 1) % 4] == points[pos.x][pos.y][dir] + 1000)
            parents[pos.x][pos.y][(dir + 1) % 4].push_back({pos, dir});
        else if (points[pos.x][pos.y][(dir + 1) % 4] > points[pos.x][pos.y][dir] + 1000)
        {
            points[pos.x][pos.y][(dir + 1) % 4] = points[pos.x][pos.y][dir] + 1000;
            parents[pos.x][pos.y][(dir + 1) % 4] = {{pos, dir}};
            q.push({pos, (dir + 1) % 4});
        }
        
        if (points[pos.x][pos.y][(dir + 3) % 4] == points[pos.x][pos.y][dir] + 1000)
            parents[pos.x][pos.y][(dir + 3) % 4].push_back({pos, dir});
        else if (points[pos.x][pos.y][(dir + 3) % 4] > points[pos.x][pos.y][dir] + 1000)
        {
            points[pos.x][pos.y][(dir + 3) % 4] = points[pos.x][pos.y][dir] + 1000;
            parents[pos.x][pos.y][(dir + 3) % 4] = {{pos, dir}};
            q.push({pos, (dir + 3) % 4});
        }
    }

    visitedPositions.resize(n, vector<bool> (m, false));
    int bestScore = min({points[endPos.x][endPos.y][0], points[endPos.x][endPos.y][1], points[endPos.x][endPos.y][2], points[endPos.x][endPos.y][3]});

    for (int i = 0; i < 4; i++)
        if (points[endPos.x][endPos.y][i] == bestScore)
            checkParent({endPos, i});
    
    cout << visited << endl;
}