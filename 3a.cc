#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    ifstream file("3.input");
    string s;

    int sum = 0;
    while (getline(file, s))
    {
        int n = s.size();
        s.append("##################### wahoo yippee yayay waba daba dub dub");

        for (int i = 0; i < n; i++)
        {
            string mulText1 = {s[i], s[i+1], s[i+2], s[i+3]};
            if (mulText1 != "mul(") continue;

            int a = 0;
            int j = i + 4;
            while (0 <= s[j] - '0' and s[j] - '0' <= 9)
            {
                a *= 10;
                a += s[j] - '0';
                j++;
            }

            if (s[j] != ',' or a >= 1000) continue;

            int b = 0;
            j++;
            while (0 <= s[j] - '0' and s[j] - '0' <= 9)
            {
                b *= 10;
                b += s[j] - '0';
                j++;
            }
            
            if (s[j] != ')' or b >= 1000) continue;

            sum += a * b;
        }
    }
    cout << sum << endl;
}