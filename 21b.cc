#include <iostream>
#include <vector>
#include <fstream>
#define int long long
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

const vector<pint> numpadCoords = {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 0}};
const pint A = {2, 1}, RIGHT = {2, 0}, UP = {1, 1}, LEFT = {0, 0}, DOWN = {1, 0};

const int ROBOTS = 26;
vector<vector<vector<vector<vector<int>>>>> cache;

int moveitboi(const int& robot, const pint& start, const pint& goal)
{
    pint movement = {goal.x - start.x, goal.y - start.y};    
    int moves = abs(movement.x) + abs(movement.y);

    if (robot == 1) 
    {
        /*for (int i = 0; i < movement.x; i++) cout << '>';
        for (int i = 0; i < -movement.y; i++) cout << 'v';
        for (int i = 0; i < movement.y; i++) cout << '^';
        for (int i = 0; i < -movement.x; i++) cout << '<';
        cout << "(A)";*/
        
        return moves;
    }

    if (cache[robot][start.x][start.y][goal.x][goal.y] != -1)
        return cache[robot][start.x][start.y][goal.x][goal.y];

    if (movement.x > 0)
    {
        if (movement.y > 0)
        {
            if (robot != ROBOTS and start == LEFT)
                moves += moveitboi(robot - 1, A, RIGHT) + moveitboi(robot - 1, RIGHT, UP) + moveitboi(robot - 1, UP, A);
            else
                moves += moveitboi(robot - 1, A, UP) + moveitboi(robot - 1, UP, RIGHT) + moveitboi(robot - 1, RIGHT, A);
        }
        else if (movement.y < 0)
        {
            if (robot == ROBOTS and start.x == 0 and goal.y == 0)
                moves += moveitboi(robot - 1, A, RIGHT) + moveitboi(robot - 1, RIGHT, DOWN) + moveitboi(robot - 1, DOWN, A);
            else
                moves += moveitboi(robot - 1, A, DOWN) + moveitboi(robot - 1, DOWN, RIGHT) + moveitboi(robot - 1, RIGHT, A);
        }
        else
            moves += moveitboi(robot - 1, A, RIGHT) + moveitboi(robot - 1, RIGHT, A);
    }
    else if (movement.x < 0)
    {
        if (movement.y > 0)
        {
            if (robot == ROBOTS and start.y == 0 and goal.x == 0)
                moves += moveitboi(robot - 1, A, UP) + moveitboi(robot - 1, UP, LEFT) + moveitboi(robot - 1, LEFT, A);
            else
                moves += moveitboi(robot - 1, A, LEFT) + moveitboi(robot - 1, LEFT, UP) + moveitboi(robot - 1, UP, A);
        }
        else if (movement.y < 0)
        {
            if (robot != ROBOTS and goal == LEFT)
                moves += moveitboi(robot - 1, A, DOWN) + moveitboi(robot - 1, DOWN, LEFT) + moveitboi(robot - 1, LEFT, A);
            else
                moves += moveitboi(robot - 1, A, LEFT) + moveitboi(robot - 1, LEFT, DOWN) + moveitboi(robot - 1, DOWN, A);
        }
        else
            moves += moveitboi(robot - 1, A, LEFT) + moveitboi(robot - 1, LEFT, A);
    }
    else
    {
        if (movement.y > 0)
            moves += moveitboi(robot - 1, A, UP) + moveitboi(robot - 1, UP, A);
        else if (movement.y < 0)
            moves += moveitboi(robot - 1, A, DOWN) + moveitboi(robot - 1, DOWN, A);
        else
            cout << "\n\n\n\n\nwtf\n\n\n\n\n" << endl;
    }

    cache[robot][start.x][start.y][goal.x][goal.y] = moves;
    return moves;
}

int complexity(string& code)
{
    int moves = 0;
    int codelength = code.length();
    for (int c = 0; c < codelength; c++)
    {
        int premoves = moves;

        int n = (code[c] == 'A') ? 10 : (code[c] - '0');
        int pre_n = (c == 0) ? 10 : ((code[c - 1] == 'A') ? 10 : (code[c - 1] - '0'));
        pint start = numpadCoords[pre_n], goal = numpadCoords[n];

        vector<vector<vector<vector<vector<int>>>>> cacheWannabe (ROBOTS + 1,
               vector<vector<vector<vector<int>>>>               (3,
                      vector<vector<vector<int>>>                (4,
                             vector<vector<int>>                 (3,
                                    vector<int>                  (4, -1)))));
        cache = cacheWannabe;

        moves += moveitboi(ROBOTS, start, goal) + 1;
    
        pint movement = {goal.x - start.x, goal.y - start.y};
        //cout << endl << movement.x << ", " << movement.y << ":\t" << moves - premoves << endl;
    }
    code.pop_back();
    //cout << moves << endl;
    return moves * stoi(code);
}

signed main()
{
    ifstream file("21.input");
    string code;

    int out = 0;
    while (getline(file, code)) out += complexity(code);
    cout << out << endl;
}