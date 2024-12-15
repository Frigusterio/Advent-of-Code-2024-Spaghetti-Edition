#include <iostream>
#include <vector>
#include <math.h>
#define x first
#define y second
#define pint pair<int, int>
using namespace std;

int n, m, N = 128;
vector<vector<vector<int>>> robots;
vector<pint> p, v;

void update(int depth, int l, int r, int d, int u, const pint& pos, int value)
{
    if (u == d and l == r)
    {
        robots[depth][pos.x][pos.y] += value;
        return;
    }

    pint mid = {(l + r) / 2, (u + d) / 2};
    if (pos.x <= mid.x and pos.y <= mid.y) update(depth + 1, l, mid.x, d, mid.y, pos, value);
    else if (pos.x <= mid.x and pos.y > mid.y) update(depth + 1, l, mid.x, mid.y + 1, u, pos, value);
    else if (pos.x > mid.x and pos.y <= mid.y) update(depth + 1, mid.x + 1, r, d, mid.y, pos, value);
    else update(depth + 1, mid.x + 1, r, mid.y + 1, u, pos, value);

    int s = r - l + 1;
    robots[depth][l / s][d / s] = robots[depth + 1][2 * l / s][2 * d / s]
                                + robots[depth + 1][2 * l / s + 1][2 * d / s]
                                + robots[depth + 1][2 * l / s][2 * d / s + 1]
                                + robots[depth + 1][2 * l / s + 1][2 * d / s + 1];
}

int get(int depth, int l, int r, int d, int u, int tl, int tr, int td, int tu)
{
    int s = r - l + 1;
    if (l == tl and r == tr and u == tu and d == td) return robots[depth][l / s][d / s];
    
    pint mid = {(l + r) / 2, (u + d) / 2};

    int out = 0;
    if (tl <= mid.x and td <= mid.y) out += get(depth + 1, l, mid.x, d, mid.y, tl, min(tr, mid.x), td, min(tu, mid.y));
    if (tl <= mid.x and tu > mid.y) out += get(depth + 1, l, mid.x, mid.y + 1, u, tl, min(tr, mid.x), max(td, mid.y + 1), tu);
    if (tr > mid.x and td <= mid.y) out += get(depth + 1, mid.x + 1, r, d, mid.y, max(tl, mid.x + 1), tr, td, min(tu, mid.y));
    if (tr > mid.x and tu > mid.y) out += get(depth + 1, mid.x + 1, r, mid.y + 1, u, max(tl, mid.x + 1), tr, max(td, mid.y + 1), tu);

    return out;
}

int main()
{
    cin >> n >> m;
    robots.resize(8);
    for (int i = 0; i < 8; i++) robots[i].resize(pow(2, i), vector<int> (pow(2, i), 0));

    pint pi, vi;
    char x;
    while (cin >> x)
    {
        cin >> x >> pi.x >> x >> pi.y >> x >> x >> vi.x >> x >> vi.y;

        p.push_back(pi);
        v.push_back(vi);
    }

    int r = p.size();
    int t = 6446;
    for (int i = 0; i < r; i++)
    {
        p[i].x = ((p[i].x + t * v[i].x) % n + n) % n;
        p[i].y = ((p[i].y + t * v[i].y) % m + m) % m;
        update(0, 0, 127, 0, 127, p[i], 1);
    }
    while (true)
    {
        //cout << t << endl;
        const pint CHECKZONE = {33, 31};
        for (int i = 0; i < n - CHECKZONE.x + 1; i++)
        {
            for (int j = 0; j < m - CHECKZONE.y + 1; j++)
            {
                if (get(0, 0, 127, 0, 127, i, i + CHECKZONE.x - 1, j, j + CHECKZONE.y - 1) >= 300)
                {
                    //cout << get(0, 0, 127, 0, 127, i, i + CHECKZONE.x - 1, j, j + CHECKZONE.y - 1) << endl;
                    cout << t << endl;
                    return 0;
                }
            }
        }

        for (int i = 0; i < r; i++)
        {
            update(0, 0, 127, 0, 127, p[i], -1);
            p[i].x = ((p[i].x + v[i].x) % n + n) % n;
            p[i].y = ((p[i].y + v[i].y) % m + m) % m;
            update(0, 0, 127, 0, 127, p[i], 1);
        }
        t++;
    }
}