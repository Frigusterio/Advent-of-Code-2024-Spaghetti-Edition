#include <iostream>
#include <vector>
#define x first
#define y second
using namespace std;

int n, m;

void printThing(vector<pair<int, int>>& p)
{
    int r = p.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool hasRobot = false;
            for (int k = 0; k < r and !hasRobot; k++)
                hasRobot = p[k].x == i and p[k].y == j;
            if (hasRobot) cout << '#';
            else cout << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cin >> n >> m;
    pair<int, int> pi, vi;
    vector<pair<int, int>> p, v;
    char x;
    cin >> x;
    while (x != 'z')
    {
        cin >> x >> pi.x >> x >> pi.y >> x >> x >> vi.x >> x >> vi.y;
        p.push_back(pi);
        v.push_back(vi);
        cin >> x;
    }

    int r = p.size();
    int t = 0;
    int centralDensity = 0;
    for (int i = 0; i < r; i++)
    {
        p[i].x = ((p[i].x + t * v[i].x) % n + n) % n;
        p[i].y = ((p[i].y + t * v[i].y) % m + m) % m;
        if (n / 2 < p[i].x and p[i].x <= n * 3 / 4) centralDensity++;
    }
    while (true)
    {
        if (centralDensity > r * 3 / 5)
        {
            cin >> x;
            cout << t << endl;
            printThing(p);
        }

        for (int i = 0; i < r; i++)
        {
            if (n / 2 < p[i].x and p[i].x <= n * 3 / 4) centralDensity--;
            p[i].x = ((p[i].x + v[i].x) % n + n) % n;
            p[i].y = ((p[i].y + v[i].y) % m + m) % m;
            if (n / 2 < p[i].x and p[i].x <= n * 3 / 4) centralDensity++;
        }
        t++;
    }
}