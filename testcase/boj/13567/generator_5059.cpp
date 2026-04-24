#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int M = rnd.next(1, 10);         // square size
    int n = rnd.next(1, 20);         // number of commands
    double pMove = rnd.next();       // probability to choose a MOVE
    double pLeft = rnd.next();       // probability that a TURN is left

    int x = 0, y = 0, dir = 0;       // 0=E,1=S,2=W,3=N
    vector<pair<string,int>> cmds;

    for (int i = 0; i < n; i++) {
        // compute maximum safe move distance
        int maxd;
        if (dir == 0)      maxd = M - x;
        else if (dir == 1) maxd = y;
        else if (dir == 2) maxd = x;
        else               maxd = M - y;

        bool canMove = (maxd > 0);
        bool doMove = canMove && (rnd.next() < pMove);

        if (doMove) {
            int d = rnd.next(1, maxd);
            cmds.emplace_back("MOVE", d);
            if (dir == 0)      x += d;
            else if (dir == 1) y -= d;
            else if (dir == 2) x -= d;
            else               y += d;
        } else {
            int t = (rnd.next() < pLeft ? 0 : 1);
            cmds.emplace_back("TURN", t);
            if (t == 0)       dir = (dir + 3) % 4; // left
            else              dir = (dir + 1) % 4; // right
        }
    }

    // Output the generated test case
    println(M, n);
    for (auto &c : cmds) {
        println(c.first, c.second);
    }

    return 0;
}
