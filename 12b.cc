#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#define x first
#define y second
using namespace std;

const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main()
{
    ifstream file("12.eric");
    string s;

    vector<string> gardenBad;

    while (getline(file, s)) gardenBad.push_back(s);

    int n = gardenBad.size();
    int m = gardenBad[0].size();

    vector<vector<int>> garden (n, vector<int> (m, -1));
    int id = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            //cout << "Checking " << i << ", " << j << ": " << gardenBad[i][j] << endl;
            if (garden[i][j] == -1)
            {
                //cout << i << ' ' << j << endl;
                queue<pair<int, int>> region;
                region.push({i, j});
                while (!region.empty())
                {
                    pair<int, int> plot = region.front();
                    region.pop();
                    if (garden[plot.x][plot.y] != -1) continue;
                    garden[plot.x][plot.y] = id;
                    //cout << plot.x << ' ' << plot.y << ": " << gardenBad[plot.x][plot.y] << ", " << garden[plot.x][plot.y] << endl;
                    for (int d = 0; d < 4; d++)
                    {
                        pair<int, int> nextPlot = {plot.x + DIRS[d].x, plot.y + DIRS[d].y};
                        bool validPos = 0 <= nextPlot.x and nextPlot.x < n and 0 <= nextPlot.y and nextPlot.y < m;
                        if (validPos and gardenBad[nextPlot.x][nextPlot.y] == gardenBad[plot.x][plot.y] and garden[nextPlot.x][nextPlot.y] == -1)
                        {
                            //cout << "Push " << nextPlot.x << ' ' << nextPlot.y << ": " << gardenBad[nextPlot.x][nextPlot.y] << ", " << garden[nextPlot.x][nextPlot.y] << endl;
                            region.push(nextPlot);
                        }
                    }
                }
                id++;
            }
        }
    }

    vector<int> areas (id, 0), perimeters (id, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            areas[garden[i][j]]++;
            for (int d = 0; d < 4; d++)
            {
                int i2 = i + DIRS[d].x, j2 = j + DIRS[d].y;
                bool validPos = 0 <= i2 and i2 < n and 0 <= j2 and j2 < m;
                if (!validPos or garden[i2][j2] != garden[i][j])
                {
                    switch (d)
                    {
                        // A = current plot
                        // X = checked plot
                    case 0:
                        // YA
                        // ZX --> Check if Y = A and Z != A
                        if (j == 0 or garden[i][j] != garden[i][j - 1] or (validPos and garden[i][j] == garden[i + 1][j - 1]))
                            perimeters[garden[i][j]]++;
                        break;

                    case 1:
                        // YZ
                        // AX --> Check if Y = A and Z != A
                        if (i == 0 or garden[i][j] != garden[i - 1][j] or (validPos and garden[i][j] == garden[i - 1][j + 1]))
                            perimeters[garden[i][j]]++;
                        break;
                    
                    case 2:
                        // ZX
                        // YA --> Check if Y = A and Z != A
                        if (j == 0 or garden[i][j] != garden[i][j - 1] or (validPos and garden[i][j] == garden[i - 1][j - 1]))
                            perimeters[garden[i][j]]++;
                        break;

                    case 3:
                        // ZY
                        // XA --> Check if Y = A and Z != A
                        if (i == 0 or garden[i][j] != garden[i - 1][j] or (validPos and garden[i][j] == garden[i - 1][j - 1]))
                            perimeters[garden[i][j]]++;
                        break;
                    }
                }
            }
        }
    }
    
    int price = 0;
    for (int i = 0; i < id; i++)
    {
        price += areas[i] * perimeters[i];
        //cout << i << ": " << perimeters[i] << endl; <-- per l'eric
    }
    cout << price << endl;
}