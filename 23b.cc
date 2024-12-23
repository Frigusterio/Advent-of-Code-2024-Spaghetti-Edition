#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
using namespace std;

vector<vector<int>> g (26 * 26);
vector<bool> visited (26 * 26, false);

int pctoi(char pc0, char pc1)
{
    return (pc0 - 'a') * 26 + (pc1 - 'a');
}

string itopc(int i)
{
    string s = "##";
    s[0] = i / 26 + 'a';
    s[1] = i % 26 + 'a';
    return s;
}

int countones(int j)
{
    int count = 0;
    while (j > 0)
    {
        count += j & 1;
        j >>= 1;
    }
    return count;
}

void buildGroup(int j, vector<int>& potentialGroup, const vector<int>& connections)
{
    int i = 0;
    while (j > 0)
    {
        if (j & 1) potentialGroup.push_back(connections[i]);
        j >>= 1;
        i++;
    }
}

bool contains(const vector<int>& v, int x)
{
    int n = v.size();
    for (int i = 0; i < n; i++) if (v[i] == x) return true;
    return false;
}

int main()
{
    ifstream file("23.input");
    string s;
    /*
    while (getline(file, s))
    {
        s[2] = ' ';
        cout << s << endl;
    }
    //*/
    //*
    while (getline(file, s))
    {
        g[pctoi(s[0], s[1])].push_back(pctoi(s[3], s[4]));
        g[pctoi(s[3], s[4])].push_back(pctoi(s[0], s[1]));
    }

    int biggestGroupSize = 1;
    vector<int> biggestGroup;
    for (int i = 0; i < 26 * 26; i++)
    {
        int combs = pow(2, g[i].size());
        for (int j = 0; j < combs; j++)
        {
            if (countones(j) + 1 <= biggestGroupSize) continue;

            vector<int> potentialGroup (0);
            buildGroup(j, potentialGroup, g[i]);

            int potentialGroupSize = potentialGroup.size();
            bool goodGroup = true;
            for (int k = 0; k < potentialGroupSize and goodGroup; k++)
                for (int l = k + 1; l < potentialGroupSize and goodGroup; l++)
                    goodGroup = contains(g[potentialGroup[k]], potentialGroup[l]);
            
            if (goodGroup)
            {
                biggestGroupSize = countones(j) + 1;
                biggestGroup = potentialGroup;
                biggestGroup.push_back(i);
            }
        }
    }

    sort(biggestGroup.begin(), biggestGroup.end());
    for (int x : biggestGroup) cout << itopc(x) << ',';
    cout << endl;
    //*/
}