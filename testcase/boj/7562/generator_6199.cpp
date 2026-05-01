#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        double r = rnd.next();
        int l, sx, sy, tx, ty;
        int type;
        if (r < 0.1) type = 0;       // trivial
        else if (r < 0.2) type = 1;  // corners
        else if (r < 0.3) type = 2;  // close
        else if (r < 0.5) type = 3;  // large random
        else type = 4;              // small/medium random

        if (type == 0) {
            // start == target
            l = rnd.next(4, 10);
            sx = rnd.next(0, l - 1);
            sy = rnd.next(0, l - 1);
            tx = sx; ty = sy;
        }
        else if (type == 1) {
            // opposite corners
            l = rnd.next(5, 20);
            vector<pair<int,int>> corners = {{0,0},{0,l-1},{l-1,0},{l-1,l-1}};
            int idx = rnd.next(0, 3);
            sx = corners[idx].first;
            sy = corners[idx].second;
            int opp = 3 - idx;
            tx = corners[opp].first;
            ty = corners[opp].second;
        }
        else if (type == 2) {
            // close neighbors, Manhattan <= 3
            l = rnd.next(4, 10);
            sx = rnd.next(0, l - 1);
            sy = rnd.next(0, l - 1);
            vector<pair<int,int>> nbr;
            for (int dx = -3; dx <= 3; dx++) {
                for (int dy = -3; dy <= 3; dy++) {
                    if (abs(dx) + abs(dy) <= 3) {
                        int nx = sx + dx, ny = sy + dy;
                        if (0 <= nx && nx < l && 0 <= ny && ny < l) {
                            if (!(nx == sx && ny == sy))
                                nbr.emplace_back(nx, ny);
                        }
                    }
                }
            }
            auto p = rnd.any(nbr);
            tx = p.first; ty = p.second;
        }
        else if (type == 3) {
            // large board random
            l = rnd.next(50, 300);
            sx = rnd.next(0, l - 1);
            sy = rnd.next(0, l - 1);
            tx = rnd.next(0, l - 1);
            ty = rnd.next(0, l - 1);
        }
        else {
            // small/medium random
            l = rnd.next(4, 30);
            sx = rnd.next(0, l - 1);
            sy = rnd.next(0, l - 1);
            tx = rnd.next(0, l - 1);
            ty = rnd.next(0, l - 1);
        }

        println(l);
        println(sx, sy);
        println(tx, ty);
    }
    return 0;
}
