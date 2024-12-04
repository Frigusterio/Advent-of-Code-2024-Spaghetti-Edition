#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

int main()
{
    ifstream file("4.input");
    string s;

    vector<string> soup;
    while (getline(file, s)) soup.push_back(s);

    int n = soup.size();
    int m = soup[0].size();

    const set<string> MS = {"MMSS", "MSSM", "SMMS", "SSMM"};

    int apparitions = 0;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            string ms = {soup[i - 1][j - 1], soup[i - 1][j + 1], soup[i + 1][j + 1], soup[i + 1][j - 1]};
            if (soup[i][j] == 'A' and MS.count(ms) > 0) apparitions++;
        }
    }
    
    cout << apparitions << endl;
}