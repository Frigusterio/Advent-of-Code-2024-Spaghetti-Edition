#include <iostream>
#include <vector>
#include <queue>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

const vector<pint> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main()
{
    const int n = 71;
    pint corruptPos;
    char x;
    vector<vector<bool>> corrupt (n, vector<bool> (n, false));

    while(cin >> corruptPos.x >> x >> corruptPos.y)
    {
        corrupt[corruptPos.x][corruptPos.y] = true;
        vector<vector<int>> ram (n, vector<int> (n, __INT_MAX__));

        priority_queue<pair<int, pint>> q;
        ram[0][0] = 0;
        q.push({0, {0, 0}});
        while (!q.empty())
        {
            int dist = -q.top().first;
            pint pos = q.top().second;
            q.pop();

            for (int d = 0; d < 4; d++)
            {
                pint dir = DIRS[d];
                pint next = {pos.x + dir.x, pos.y + dir.y};
                if (0 <= next.x and next.x < n and 0 <= next.y and next.y < n and !corrupt[next.x][next.y] and ram[next.x][next.y] > dist + 1)
                {
                    ram[next.x][next.y] = dist + 1;
                    q.push({-(dist + 1), next});
                }
            }
        }

        /*for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (ram[i][j] == -1) cout << '#';
                else if (ram[i][j] == __INT_MAX__) cout << '.';
                else cout << ram[i][j];
            }
            cout << endl;
        }*/

        if (ram[n - 1][n - 1] == __INT_MAX__)
        {
            cout << corruptPos.x << ',' << corruptPos.y << endl;
            return 0;
        }
    }
}