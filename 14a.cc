#include <iostream>
#include <vector>
#define x first
#define y second
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    pair<int, int> p, v;
    vector<int> q (4);
    char x;
    while (cin >> x >> x >> p.x >> x >> p.y >> x >> x >> v.x >> x >> v.y)
    {
        p.x = ((p.x + 100 * v.x) % n + n) % n;
        p.y = ((p.y + 100 * v.y) % m + m) % m;

        if (p.x == n / 2 or p.y == m / 2) continue;

        q[(p.x < n / 2) + 2 * (p.y < m / 2)]++;
    }

    cout << q[0] << ' ' << q[1] << ' ' << q[2] << ' ' << q[3] << endl;
    cout << q[0]  * q[1] * q[2] * q[3] << endl;
}