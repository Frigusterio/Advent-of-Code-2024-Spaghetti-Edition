#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream file("1.input");
    string s;

    vector<int> joe, mama;
    while (getline(file, s, ' '))
    {
        joe.push_back(stoi(s));
        getline(file, s, ' ');
        getline(file, s, ' ');
        getline(file, s);
        mama.push_back(stoi(s));
    }

    int n = joe.size();
    for (int i = 0; i < n; i++)
    {
        cout << joe[i] << ' ' << mama[i] << endl;
    }
    
}