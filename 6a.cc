#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Pos
{
    int x, y;
};

int main()
{
    ifstream file("6.input");
    string s;

    vector<string> map;
    while (getline(file, s)) map.push_back(s);

    int n = map.size();
    int m = map[0].size();

    Pos pos;
    int dir = 0;
    const vector<Pos> DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == '^')
                pos = {i, j};

    int visited = 0;
    while (0 <= pos.x and pos.x < n and 0 <= pos.y and pos.y < m)
    {
        if (map[pos.x][pos.y] != 'X')
        {
            visited++;
            map[pos.x][pos.y] = 'X';
        }

        int newx = pos.x + DIRS[dir].x;
        int newy = pos.y + DIRS[dir].y;

        if (0 <= newx and newx < n and 0 <= newy and newy < m and map[newx][newy] == '#')
        {
            dir = (dir + 1) % 4;
            newx = pos.x + DIRS[dir].x;
            newy = pos.y + DIRS[dir].y;
        }
        pos = {newx, newy};
    }
    cout << visited << endl;
}