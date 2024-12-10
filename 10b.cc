#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#define x first 
#define y second
using namespace std;

int n, m;
vector<string> v;
const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int score(int i0, int j0)
{
    int amountOfNinesReached = 0;
    queue<vector<int>> q;
    q.push({i0, j0, '0'});
    while(!q.empty())
    {
        int i = q.front()[0], j = q.front()[1], h = q.front()[2];
        q.pop();

        if (h == '9')
        {
            amountOfNinesReached++;
            continue;
        }

        for (int d = 0; d < 4; d++)
        {
            int newI = i + DIRS[d].x;
            int newJ = j + DIRS[d].y;

            if (0 <= newI and newI < n and 0 <= newJ and newJ < m and v[newI][newJ] == h + 1)
            {
                q.push({newI, newJ, h + 1});
            }
        }
    }

    return amountOfNinesReached;
}

int main()
{
    ifstream file("10.input");
    string s;
    while (getline(file, s)) v.push_back(s);

    n = v.size();
    m = v[0].size();

    int totalScore = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (v[i][j] == '0')
                totalScore += score(i, j);

    cout << totalScore << endl;
}