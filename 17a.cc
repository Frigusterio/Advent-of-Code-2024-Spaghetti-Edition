#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

signed main()
{
    const int A = 4, B = 5, C = 6;
    vector<int> regfile = {0, 1, 2, 3, 4, 5, 6, 7};
    
    string x;
    vector<int> instructions (0);
    cin >> x >> x >> regfile[A] >> x >> x >> regfile[B] >> x >> x >> regfile[C] >> x;
    char c;
    while (cin >> c)
    {
        if (c == ',') continue;
        instructions.push_back(c - '0');
    }

    int pc = 0;
    int n = instructions.size();
    while (pc < n)
    {
        int instruction = instructions[pc];
        if (pc + 1 >= n) cout << "wtf" << endl;
        int operand = instructions[pc + 1];
        pc += 2;

        //cout << instruction << ", " << operand << endl;
        //cout << (A & 7) << ' ' << (A >> ((A & 7) ^ 1)) << endl;
        //cout << (((A & 7) ^ (A >> ((A & 7) ^ 1)) ^ 5) & 7) << endl;

        switch (instruction)
        {
        case 0:
            regfile[A] >>= regfile[operand];
            break;
        case 1:
            regfile[B] ^= operand;
            break;
        case 2:
            regfile[B] = regfile[operand] & 7;
            break;
        case 3:
            if (regfile[A] != 0) pc = operand;
            break;
        case 4:
            regfile[B] ^= regfile[C];
            break;
        case 5:
            cout << (regfile[operand] & 7) << ',';
            break;
        case 6:
            regfile[B] = regfile[A] >> regfile[operand];
            break;
        case 7:
            regfile[C] = regfile[A] >> regfile[operand];
            break;
        }

        //cout << regfile[A] << "; " << regfile[B] << "; " << regfile[C] << endl;
    }
    cout << endl;
}