#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;
using namespace chrono;

const vector<pint> coords = {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 0}};

int complexity(string& code)
{
    int moves = 0;
    for (int c = 0; c < 4; c++)
    {
        int premoves = moves;

        int n = (code[c] == 'A') ? 10 : (code[c] - '0');
        int pre_n = (c == 0) ? 10 : ((code[c - 1] == 'A') ? 10 : (code[c - 1] - '0'));
        pint start = coords[pre_n], goal = coords[n];
        pint movement = {goal.x - start.x, goal.y - start.y};

        moves += abs(movement.x) + abs(movement.y);
        if (movement.x > 0)
        {
            if (movement.y > 0) moves += 17;
            else if (movement.y < 0)
            {
                if (start.x == 0 and goal.y == 0) moves += 19;
                else moves += 15;
            }
            else moves += 9;
        }
        else if (movement.x < 0)
        {
            if (movement.y > 0)
            {
                if (start.y == 0 and goal.x == 0) moves += 23;
                else moves += 19;
            }
            else if (movement.y < 0) moves += 19;
            else moves += 17;
        }
        else
        {
            if (movement.y > 0) moves += 11;
            else if (movement.y < 0) moves += 15;
            else moves++;
        }

        //cout << movement.x << ", " << movement.y << ": " << moves - premoves << endl;
    }
    code.pop_back();
    //cout << moves << ", " << code << ", " << stoi(code) << endl;
    return moves * stoi(code);
}

int main()
{
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < 1000; i++)
    {
        ifstream file("21.input");
        string code;

        int out = 0;
        while (getline(file, code)) out += complexity(code);
        cout << out << endl;
    }
    
    auto t2 = high_resolution_clock::now();
    cout << duration_cast<microseconds>(t2 - t1).count() << " microseconds" << endl;
}