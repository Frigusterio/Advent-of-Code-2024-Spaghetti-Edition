#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> u, v;
    int a, b;
    while (cin >> a >> b)
    {
        u.push_back(a);
        v.push_back(b);
    }

    sort(u.begin(), u.end());
    sort(v.begin(), v.end());

    int n = u.size();
    int out = 0;
    for (int i = 0; i < n; i++)
    {
        out += abs(u[i] - v[i]);
    }
    
    cout << out << endl;
}