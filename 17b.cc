#include <iostream>
#include <vector>
using namespace std;

//vector<int> instructions = {0,3,5,4,3,0};
vector<int> instructions = {2,4,1,1,7,5,4,6,0,3,1,4,5,5,3,0};
//int out = -1;

void fuckyouspiderman(int i, long long p)
{
    for (int j = 0; j < 8 /*and out == -1*/; j++)
    {
        long long q = (p << 3) + j;
        //cout << "Checking in " << i << ", " << j << ": " << (((q & 7) ^ (q >> ((q & 7) ^ 1)) ^ 5) & 7) << " vs " << instructions[i] << endl;
        //cout << "Testing in " << i << ", " << j << ": " << ((q >> 3) & 7) << " vs " << instructions[i] << endl;
        if ((((q & 7) ^ (q >> ((q & 7) ^ 1)) ^ 5) & 7) == instructions[i])
        //if (((q >> 3) & 7) == instructions[i])
        {
            if (i > 0) fuckyouspiderman(i - 1, q);
            else 
            {
                cout << q << "\n";
                exit(0);
            }
        }
    }
}

signed main()
{
    /*int startA, startB, startC;
    string x;
    cin >> x >> x >> startA >> x >> x >> startB >> x >> x >> startC >> x;

    const int A = 4, B = 5, C = 6;
    
    char c;
    while (cin >> c)
    {
        if (c == ',') continue;
        instructions.push_back(c - '0');
    }*/

    /*
        Test input:
        0,3 , 5,4 , 3,0

        A = A / 8
        out A % 8
        if (A != 0) pc = 0

        --> out = A / 8 % 8

        Real input:
        2,4, 1,1, 7,5, 4,6, 0,3, 1,4, 5,5, 3,0

        B = A % 8
        B = B xor 1
        C = A / 2^B
        B = B xor C
        A = A / 8
        B = B xor 4
        out B % 8
        if (A != 0) pc = 0

        --> out = (A % 8 xor (A >> (A % 8 xor 1)) xor 5) % 8

        ((A >> 0) % 8 xor ((A >> 0) >> ((A >> 0) % 8 xor 1)) xor 5) % 8 = 2
        ((A >> 3) % 8 xor ((A >> 3) >> ((A >> 3) % 8 xor 1)) xor 5) % 8 = 4
        ((A >> 6) % 8 xor ((A >> 6) >> ((A >> 6) % 8 xor 1)) xor 5) % 8 = 1
        ((A >> 9) % 8 xor ((A >> 9) >> ((A >> 9) % 8 xor 1)) xor 5) % 8 = 1
        ...
        ((A >> 45) % 8 xor ((A >> 45) >> ((A >> 45) % 8 xor 1)) xor 5) % 8 = 0
        Suppose P = A >> 45 € {0..7}
        (P xor (P >> (P xor 1)) xor 5) % 8 = 0
        (P xor (P == 1) xor 5) % 8 = 0
        If P == 1, 5 % 8 != 0 --> P = 5 --> A >= 5 << 45

        ((A >> 42) % 8 xor ((A >> 42) >> ((A >> 42) % 8 xor 1)) xor 5) % 8 = 3
        A >> 45 = 5 -> A >> 42 = 5 << 3 + Q = 40 + Q, where Q € {0..7}
        (Q xor ((40 + Q) >> (Q xor 1)) xor 5) % 8 = 3
        (Q xor (5 >> (Q xor 1 - 3) + (Q == 1)) xor 5) % 8 = 3

        bruh just code it fr fr
    */

    fuckyouspiderman(instructions.size() - 1, 0);

    //cout << out << endl;
}