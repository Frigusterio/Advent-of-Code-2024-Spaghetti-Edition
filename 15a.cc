#include <iostream>
#include <vector>
#include <fstream>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

int n, m;
vector<string> warehouse;

void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << warehouse[i][j];
        cout << endl;
    }
}

bool move(const pint& pos, const pint& dir)
{
    //cout << pos.x << ", " << pos.y << " | " << dir.x << ", " << dir.y << ": ";
    pint dest = {pos.x + dir.x, pos.y + dir.y};
    //cout << warehouse[pos.x][pos.y] << ", " << warehouse[dest.x][dest.y] << endl;

    if (warehouse[dest.x][dest.y] == '#') return false;
    if (warehouse[dest.x][dest.y] == 'O')
    {
        if (move(dest, dir))
        {
            //cout << "Moved " << pos.x << ", " << pos.y << " to " << dest.x << ", " << dest.y << endl;
            warehouse[dest.x][dest.y] = warehouse[pos.x][pos.y];
            warehouse[pos.x][pos.y] = '.';
            return true;
        }
        else return false;
    }
    //cout << "Moved " << pos.x << ", " << pos.y << " to " << dest.x << ", " << dest.y << endl;
    warehouse[dest.x][dest.y] = warehouse[pos.x][pos.y];
    warehouse[pos.x][pos.y] = '.';
    return true;
}

int main()
{
    ifstream file("15.input");
    string s;
    string moves = "";
    pint robot = {-1, -1};

    getline(file, s);
    while (s != "")
    {
        warehouse.push_back(s);
        getline(file, s);
    }

    n = warehouse.size();
    m = warehouse[0].size();

    for (int i = 0; i < n and robot.x == -1; i++)
        for (int j = 0; j < m and robot.x == -1; j++)
            if (warehouse[i][j] == '@')
                robot = {i, j};

    while (getline(file, s)) moves.append(s);

    const int MOVES = moves.size();

    for (int mov = 0; mov < MOVES; mov++)
    {   
        //cout << mov << ": " << moves[mov] << endl;
        //cout << "Rob at " << robot.x << ", " << robot.y << endl;

        switch (moves[mov])
        {
        case 'v': // i
            if (move(robot, {1, 0}))
                robot = {robot.x + 1, robot.y};
            break;
        
        case '>': // j
            if (move(robot, {0, 1}))
                robot = {robot.x, robot.y + 1};
            break;

        case '^': // -i
            if (move(robot, {-1, 0}))
                robot = {robot.x - 1, robot.y};
            break;
            
        case '<': // -j
            if (move(robot, {0, -1}))
                robot = {robot.x, robot.y - 1};
            break;
        }
    }  

    int out = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (warehouse[i][j] == 'O')
                out += 100 * i + j;
    cout << out << endl;
}