#include <iostream>
#include <vector>
#include <fstream>
#include <map>
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
        calcValue(result);
    }
}

signed main()
{
    ifstream file("24.input");
    string s;
    vector<string> initialValues;
    while (getline(file, s))
    {
        if (s == "") break;
        values[{s[0], s[1], s[2]}] = s[5] - '0';
        initialValues.push_back({s[0], s[1], s[2]});
    }

    while (getline(file, s))
    {
        // I tinkered the input to change OR to ORR
        string operand1 = {s[0], s[1], s[2]};
        string operation = {s[4], s[5], s[6]};
        string operand2 = {s[8], s[9], s[10]};
        string result = {s[15], s[16], s[17]};
        doors[operand1].push_back({operand2, result, operation});
        doors[operand2].push_back({operand1, result, operation});
    }

    int n = initialValues.size();
    for (int i = 0; i < n; i++)
        calcValue(initialValues[i]);

    int out = 0;
    for (int i = 99; i >= 0; i--)
    {
        string z = {'z', char(i / 10 + '0'), char(i % 10 + '0')};
        out <<= 1;
        out += values[z];
    }
    cout << out << endl;
}