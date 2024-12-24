#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <math.h>
#include <algorithm>
#define int long long
using namespace std;

map<string, bool> values;
map<string, vector<vector<string>>> doors; // 1st operand, {{2nd operand, result, operation}}

void calcValue(string operand1)
{
    for (vector<string> door : doors[operand1])
    {
        string operand2 = door[0];
        string result = door[1];
        const char operation = door[2][0];
        if (!values.count(operand2) or values.count(result)) continue;
        switch (operation)
        {
        case 'A':
            values[result] = values[operand1] and values[operand2];
            break;
        
        case 'O':
            values[result] = values[operand1] or values[operand2];
            break;

        case 'X':
            values[result] = values[operand1] xor values[operand2];
            break;
        }
        cout << operand1 << ' ' << door[2] << ' ' << operand2 << " -> " << result << endl;
        calcValue(result);
    }
}

void printBinary(int d)
{
    string b = "";
    while (d > 0)
    {
        b.push_back((d & 1) + '0');
        d >>= 1;
    }
    for (int i = b.size() - 1; i >= 0; i--) cout << b[i];
    cout << endl;
}

signed main()
{
    ifstream file("24.input");
    string s;
    vector<string> initialValues;
    int x = 0, y = 0;
    while (getline(file, s))
    {
        if (s == "") break;
        values[{s[0], s[1], s[2]}] = s[5] - '0';
        initialValues.push_back({s[0], s[1], s[2]});

        if (s[0] == 'x') x += (s[5] - '0') * pow(2, 10 * (s[1] - '0') + (s[2] - '0'));
        if (s[0] == 'y') y += (s[5] - '0') * pow(2, 10 * (s[1] - '0') + (s[2] - '0'));
    }

    map<string, string> swaps;
    swaps["nnt"] = "gws", swaps["gws"] = "nnt";
    swaps["z13"] = "npf", swaps["npf"] = "z13";
    swaps["z19"] = "cph", swaps["cph"] = "z19";
    swaps["z33"] = "hgj", swaps["hgj"] = "z33";
    vector<string> swappedGuys = {"nnt", "z13", "z19", "z33", "gws", "npf", "cph", "hgj"};
    sort(swappedGuys.begin(), swappedGuys.end());
    for (string swappedGuy : swappedGuys) cout << swappedGuy << ',';
    cout << endl;
    return 0;

    while (getline(file, s))
    {
        // I tinkered the input to change OR to ORR
        string operand1 = {s[0], s[1], s[2]};
        string operation = {s[4], s[5], s[6]};
        string operand2 = {s[8], s[9], s[10]};
        string result = {s[15], s[16], s[17]};
        if (swaps.count(result)) result = swaps[result];
        doors[operand1].push_back({operand2, result, operation});
        doors[operand2].push_back({operand1, result, operation});
    }

    int n = initialValues.size();
    for (int i = 0; i < n; i++)
        calcValue(initialValues[i]);

    int z = 0;
    for (int i = 99; i >= 0; i--)
    {
        string zbit = {'z', char(i / 10 + '0'), char(i % 10 + '0')};
        z <<= 1;
        z += values[zbit];
    }
    //cout << x << " + " << y << " = " << x + y << " vs " << z << endl;
    //cout << abs(z - x - y) << ", " << (z ^ (x + y)) << endl;
    //printBinary((x + y) ^ z);
}