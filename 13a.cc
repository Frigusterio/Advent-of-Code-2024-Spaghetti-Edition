#include <iostream>
#include <vector>
#define int long long
using namespace std;

signed main()
{
    int tokens = 0;
    int ax, ay, bx, by, px, py;
    string x1;
    char x2;

    while (cin >> x1 >> x1 >> x2 >> x2 >> ax >> x2 >> x2 >> x2 >> ay
               >> x1 >> x1 >> x2 >> x2 >> bx >> x2 >> x2 >> x2 >> by
               >> x1 >> x2 >> x2 >> px >> x2 >> x2 >> x2 >> py)
    {
        /*
        ( ax bx | px )     ( ax            bx |            px)
        ( ay by | py ) --> (  0 by - bx*ay/ax | py - px*ay/ax) --> 
        */

        px += 10000000000000;
        py += 10000000000000;

        int detM = ax * by - ay * bx;
        int detA = px * by - py * bx;
        int detB = ax * py - ay * px;

        if (detM == 0)
        {
            cout << "uh oh, stinky!" << endl;
            return 0;
        }

        if (detA % detM == 0 and detB % detM == 0)
        {
            tokens += 3 * detA / detM + detB / detM;
        }
    }

    cout << tokens << endl;
}