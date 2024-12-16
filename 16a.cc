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

int main()
{
    ifstream file("16.input");
    string s;
    vector<string> maze;
    while (getline(file, s)) maze.push_back(s);

    int n = maze.size();
    int m = maze[0].size();
    pint start = {n - 2, 1};
    pint end = {1, m - 2};

    queue<pair<pint, int>> q;
    vector<vector<vector<int>>> points (n, vector<vector<int>> (m, vector<int> (4, __INT_MAX__)));
    q.push({start, 1});
    points[start.x][start.y][1] = 0;

    while (!q.empty())
    {
        pint pos = q.front().first;
        int dir = q.front().second;
        q.pop();

        //Maze works in movements of 2 (epic optimization)
        pint front = {pos.x + DIRS[dir].x, pos.y + DIRS[dir].y};
        pint next = {pos.x + 2 * DIRS[dir].x, pos.y + 2 * DIRS[dir].y};

        if (maze[front.x][front.y] != '#' and points[next.x][next.y][dir] > points[pos.x][pos.y][dir] + 2)
        {
            points[next.x][next.y][dir] = points[pos.x][pos.y][dir] + 2;
            q.push({next, dir});
        }
        if (points[pos.x][pos.y][(dir + 1) % 4] > points[pos.x][pos.y][dir] + 1000)
        {
            points[pos.x][pos.y][(dir + 1) % 4] = points[pos.x][pos.y][dir] + 1000;
            q.push({pos, (dir + 1) % 4});
        }
        if (points[pos.x][pos.y][(dir + 3) % 4] > points[pos.x][pos.y][dir] + 1000)
        {
            points[pos.x][pos.y][(dir + 3) % 4] = points[pos.x][pos.y][dir] + 1000;
            q.push({pos, (dir + 3) % 4});
        }
    }

    cout << min({points[end.x][end.y][0], points[end.x][end.y][1], points[end.x][end.y][2], points[end.x][end.y][3]}) << endl;
}