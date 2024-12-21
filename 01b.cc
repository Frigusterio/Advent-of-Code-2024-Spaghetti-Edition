#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int biggest = 0;
    vector<int> u, v;
    int a, b;
    while (cin >> a >> b)
    {
        u.push_back(a);
        v.push_back(b);
        biggest = max({biggest, a, b});
    }

    int n = u.size(), m = v.size();
    vector<int> apparitions (biggest + 1, 0);

    for (int i = 0; i < m; i++)
    {
        apparitions[v[i]]++;
    }

    int out = 0;
    for (int i = 0; i < n; i++)
    {
        out += u[i] * apparitions[u[i]];
    }
    cout << out << endl;
}