#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream file("25.input");
    string s;

    int checking = 0; //0 -> nothing, 1 -> key, 2 -> lock
    vector<vector<int>> locks, keys;

    while (getline(file, s))
    {
        if (checking == 0)
        {
            if (s == ".....")
            {
                checking = 1;
                keys.push_back({-1, -1, -1, -1, -1});
            }
            else
            {
                checking = 2;
                locks.push_back({0, 0, 0, 0, 0});
            }
        }
        else if (s == "") checking = 0;
        else if (checking == 1)
        {
            for (int i = 0; i < 5; i++)
                if (s[i] == '#') keys[keys.size() - 1][i]++;
        }
        else
        {
            for (int i = 0; i < 5; i++)
                if (s[i] == '#') locks[locks.size() - 1][i]++;
        }
    }

    int n = locks.size();
    int m = keys.size();

    int fits = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (locks[i][0] + keys[j][0] <= 5
            and locks[i][1] + keys[j][1] <= 5
            and locks[i][2] + keys[j][2] <= 5
            and locks[i][3] + keys[j][3] <= 5
            and locks[i][4] + keys[j][4] <= 5) fits++;
        }
    }
    cout << fits << endl;
}