#include <iostream>
#include <vector>
#include <fstream>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

int n, m;
vector<string> w;

void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << w[i][j];
        cout << endl;
    }
}

bool canMove(const pint& pos, const pint& dir)
{
    pint pos1, pos2;
    if (w[pos.x][pos.y] == '[')
    {
        pos1 = pos;
        pos2 = {pos.x, pos.y + 1};
    }
    else if (w[pos.x][pos.y] == ']')
    {
        pos1 = {pos.x, pos.y - 1};
        pos2 = pos;
    }
    else
    {
        pos1 = pos;
        pos2 = pos;
    }
    pint dest1 = {pos1.x + dir.x, pos1.y + dir.y}, dest2 = {pos2.x + dir.x, pos2.y + dir.y};

    //cout << "I'd really want to move to " << dest1.x << ", " << dest1.y << " and " << dest2.x << ", " << dest2.y << " from " << pos1.x << ", " << pos1.y << " and " << pos2.x << ", " << pos2.y << endl;
    //cout << w[pos.x][pos.y] << ", " << w[dest.x][dest.y] << endl;

    if (w[dest1.x][dest1.y] == '#' or w[dest2.x][dest2.y] == '#') return false;

    return (w[dest1.x][dest1.y] == '.' or dest1 == pos2 or canMove(dest1, dir))
       and (dest1 == dest2 or w[dest2.x][dest2.y] == '.' or dest2 == pos1 or canMove(dest2, dir));
}

void move(const pint& pos, const pint& dir)
{
    if (w[pos.x][pos.y] == '.') return;

    //cout << pos.x << ", " << pos.y << " | " << dir.x << ", " << dir.y << ": ";
    
    pint pos1, pos2;
    if (w[pos.x][pos.y] == '[')
    {
        pos1 = pos;
        pos2 = {pos.x, pos.y + 1};
    }
    else if (w[pos.x][pos.y] == ']')
    {
        pos1 = {pos.x, pos.y - 1};
        pos2 = pos;
    }
    else
    {
        pos1 = pos;
        pos2 = pos;
    }
    pint dest1 = {pos1.x + dir.x, pos1.y + dir.y}, dest2 = {pos2.x + dir.x, pos2.y + dir.y};
    //cout << w[pos.x][pos.y] << ", " << w[dest.x][dest.y] << endl;
    
    if (dest1 != pos2) move(dest1, dir);
    if (dest2 != pos1) move(dest2, dir);

    char wpos2 = w[pos2.x][pos2.y];
    w[dest1.x][dest1.y] = w[pos1.x][pos1.y];
    w[pos1.x][pos1.y] = '.';
    w[dest2.x][dest2.y] = wpos2;
    if (dest1 != pos2) w[pos2.x][pos2.y] = '.';
}

int main()
{
    ifstream file("15.input");
    string s;
    string moves = "";
    pint robot = {-1, -1};

    getline(file, s);
    int wLine = 0;
    while (s != "")
    {
        w.push_back("");

        int saucyJack = s.size();
        for (int i = 0; i < saucyJack; i++)
        {
            switch (s[i])
            {
            case '#':
                w[wLine].append("##");
                break;
            
            case 'O':
                w[wLine].append("[]");
                break;

            case '.':
                w[wLine].append("..");
                break;

            case '@':
                w[wLine].append("@.");
                break;
            }
        }
        
        wLine++;
        getline(file, s);
    }

    n = w.size();
    m = w[0].size();

    for (int i = 0; i < n and robot.x == -1; i++)
        for (int j = 0; j < m and robot.x == -1; j++)
            if (w[i][j] == '@')
                robot = {i, j};

    //print();

    while (getline(file, s)) moves.append(s);

    const int MOVES = moves.size();

    for (int mov = 0; mov < MOVES; mov++)
    {   
        //cout << mov << ": " << moves[mov] << endl;
        //cout << "Rob at " << robot.x << ", " << robot.y << endl;

        switch (moves[mov])
        {
        case 'v': // i
            if (canMove(robot, {1, 0}))
            {
                move(robot, {1, 0});
                robot = {robot.x + 1, robot.y};
            }
            break;
        
        case '>': // j
            if (canMove(robot, {0, 1}))
            {
                move(robot, {0, 1});
                robot = {robot.x, robot.y + 1};
            }
            break;

        case '^': // -i
            if (canMove(robot, {-1, 0}))
            {
                move(robot, {-1, 0});
                robot = {robot.x - 1, robot.y};
            }
            break;
            
        case '<': // -j
            if (canMove(robot, {0, -1}))
            {
                move(robot, {0, -1});
                robot = {robot.x, robot.y - 1};
            }
            break;
        }
    }  

    int out = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (w[i][j] == '[')
                out += 100 * i + j;
    cout << out << endl;
}