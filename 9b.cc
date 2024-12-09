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

    int fileID = (n - 1) / 2;
    n = blocks.size();
    int i = n - 1;
    
    while (fileID >= 0)
    {
        //cout << "Checking file ID " << fileID << " in spot " << i << endl;

        while (blocks[i] != fileID) i--;
        int fileSize = 0;
        while (blocks[i] == fileID)
        {
            fileSize++;
            i--;
        }

        int j = 0, spacesInARow = 0;
        while (spacesInARow < fileSize and j <= i)
        {
            if (blocks[j] == -1) spacesInARow++;
            else spacesInARow = 0;
            j++;
        }

        fileID--;

        if (spacesInARow  != fileSize) continue;

        // 00611...j223334..i555.. <-- Example of finding place for file 5

        for (int k = 1; k <= fileSize; k++) swap(blocks[j - k], blocks[i + k]);
    }
    
    /*for (int x : blocks)
    {
        if (x == -1) cout << '.';
        else cout << x;
    }
    cout << endl;*/
    
    int checksum = 0;
    for (int i = 0; i < n; i++)
        if (blocks[i] != -1)
            checksum += i * blocks[i];
    cout << checksum << endl;
}