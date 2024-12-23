#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

signed main()
{
    ifstream file("22.input");
    string s;
    const int M = 16777216 - 1;
    const int Ñ = 2000;
    vector<vector<int>> changes (Ñ), numbers (Ñ);
    while (getline(file, s))
    {
        int n = stoi(s);
        for (int i = 0; i < Ñ; i++)
        {
            int pre_n = n;
            n ^= n << 6;
            n &= M;
            n ^= n >> 5;
            n ^= n << 11;
            n &= M;

            numbers[i].push_back(n % 10);
            changes[i].push_back(n % 10 - pre_n % 10);
        }
    }
    int monkeys = numbers[0].size();

    int out = 0;
    vector<int> bestprices;
    int besta, bestb, bestc, bestd;

    for (int n1 = 0; n1 < 10; n1++)
    {
        cout << "Checking n1 = " << n1 << endl;
        for (int n2 = 0; n2 < 10; n2++)
        {
            cout << "Checking n2 = " << n2 << endl;
            for (int n3 = 0; n3 < 10; n3++)
            {
                for (int n4 = 0; n4 < 10; n4++)
                {
                    for (int n5 = 0; n5 < 10; n5++)
                    {
                        if (n1 != 0 and n2 != 0 and n3 != 0 and n4 != 0 and n5 != 0) continue;
                        int a = n2 - n1, b = n3 - n2, c = n4 - n3, d = n5 - n4;

                        int sum = 0;
                        vector<int> prices (0);
                        for (int i = 0; i < monkeys; i++)
                        {
                            bool foundSeq = false;
                            for (int j = 3; j < Ñ; j++)
                            {
                                if (changes[j - 3][i] == a and changes[j - 2][i] == b and changes[j - 1][i] == c and changes[j][i] == d)
                                {
                                    prices.push_back(numbers[j][i]);
                                    sum += numbers[j][i];
                                    foundSeq = true;
                                    break;
                                }
                            }
                            if (!foundSeq) prices.push_back(0);
                        }
                        if (out < sum) 
                        {
                            out = sum;
                            bestprices = prices;
                            besta = a, bestb = b, bestc = c, bestd = d;
                        }
                    }
                }
            }
        }
    }
    
    /*
    for (int a = -9; a < 10; a++)
    {
        cout << "Checking a = " << a << endl;
        for (int b = -9; b < 10; b++)
        {
            cout << "Checking b = " << b << endl;
            for (int c = -9; c < 10; c++)
            {
                for (int d = -9; d < 10; d++)
                {
                    int sum = 0;
                    vector<int> prices (0);
                    for (int i = 0; i < monkeys; i++)
                    {
                        bool foundSeq = false;
                        for (int j = 3; j < Ñ; j++)
                        {
                            if (changes[j - 3][i] == a and changes[j - 2][i] == b and changes[j - 1][i] == c and changes[j][i] == d)
                            {
                                prices.push_back(numbers[j][i]);
                                sum += numbers[j][i];
                                foundSeq = true;
                                break;
                            }
                        }
                        if (!foundSeq) prices.push_back(0);
                    }
                    if (out < sum) 
                    {
                        out = sum;
                        bestprices = prices;
                        besta = a, bestb = b, bestc = c, bestd = d;
                    }
                }
            }
        } 
    }
    */

    cout << besta << ", " << bestb << ", " << bestc << ", " << bestd << endl;
    for (int x : bestprices) cout << x << ' ';
    cout << endl;
    cout << out << endl;
}