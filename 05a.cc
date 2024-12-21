#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

vector<int> readNumbersFromLine(string& s)
{
    vector<int> v (1, 0);
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        if (s[i] == ',') v.push_back(0);
        else v[v.size() - 1] = v[v.size() - 1] * 10 + (s[i] - '0');
    }

    return v;
}

int main()
{
    ifstream file("5.input");
    string s;

    set<pair<int, int>> rules;

    while (getline(file, s))
    {
        if (s == "") break;

        int x = 10 * (s[0] - '0') + s[1] - '0';
        int y = 10 * (s[3] - '0') + s[4] - '0';
        rules.insert({y, x});
    }

    int sum = 0;

    while (getline(file, s))
    {
        vector<int> v = readNumbersFromLine(s);
        int n = v.size();

        bool correct = true;

        for (int i = 0; i < n and correct; i++)
            for (int j = i + 1; j < n and correct; j++)
                correct = rules.count({v[i], v[j]}) == 0;
        
        if (correct) sum += v[n / 2];
    }

    cout << sum << endl;
}