#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

void swap(int& a, int& b)
{
    int a_ = a;
    a = b;
    b = a_;
}

signed main()
{
    ifstream file("9.input");
    string disk;
    getline(file, disk);

    vector<int> blocks;

    int n = disk.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < disk[i] - '0'; j++)
        {
            if (i % 2 == 0) blocks.push_back(i / 2);
            else blocks.push_back(-1);
        }
    }

    n = blocks.size();
    
    int firstSpace = 0, lastNum = n - 1;

    while (firstSpace < lastNum)
    {
        if (blocks[firstSpace] != -1) firstSpace++;
        if (blocks[lastNum] == -1) lastNum--;
        if (blocks[firstSpace] == -1 and blocks[lastNum] != -1) swap(blocks[firstSpace], blocks[lastNum]);
    }

    int checksum = 0;
    int i = 0;
    while (i < n and blocks[i] != -1)
    {
        checksum += i * blocks[i];
        i++;
    }
    cout << checksum << endl;
}