#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Dir
{
    int x, y;
};

int main()
{
    ifstream file("4.input");
    string s;

    vector<string> soup;
    while (getline(file, s)) soup.push_back(s);

    int n = soup.size();
    int m = soup[0].size();

    const string XMAS = "XMAS";
    const vector<Dir> DIRS = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    int apparitions = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int d = 0; d < 8; d++)
            {
                int k = 0;
                int i2 = i, j2 = j;
                while (k < 4 and 0 <= i2 and i2 < n and 0 <= j2 and j2 < m and soup[i2][j2] == XMAS[k])
                {
                    i2 += DIRS[d].x;
                    j2 += DIRS[d].y;
                    k++;
                }
                if (k == 4) apparitions++;
            }
        }
    }

    cout << apparitions << endl;
}