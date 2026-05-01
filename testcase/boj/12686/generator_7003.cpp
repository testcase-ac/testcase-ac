#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int type = rnd.next(0, 4);
        int R, C;
        vector<string> g;
        if (type == 0) {
            // trivial 1x1
            R = C = 1;
            g = {"K"};
        } else if (type == 1) {
            // full open
            R = rnd.next(2, 8);
            C = rnd.next(2, 8);
            g.assign(R, string(C, '.'));
            int kr = rnd.next(0, R-1), kc = rnd.next(0, C-1);
            g[kr][kc] = 'K';
        } else if (type == 2) {
            // full burned except K
            R = rnd.next(2, 8);
            C = rnd.next(2, 8);
            g.assign(R, string(C, '#'));
            int kr = rnd.next(0, R-1), kc = rnd.next(0, C-1);
            g[kr][kc] = 'K';
        } else if (type == 3) {
            // striped pattern
            R = rnd.next(3, 8);
            C = rnd.next(3, 8);
            g.assign(R, string(C, '#'));
            bool horiz = rnd.next(0, 1) == 0;
            int width = rnd.next(1, (horiz ? R : C));
            // build stripes: start unburned
            if (horiz) {
                for (int i = 0; i < R; i++) {
                    bool unb = ((i / width) % 2) == 0;
                    for (int j = 0; j < C; j++)
                        g[i][j] = unb ? '.' : '#';
                }
            } else {
                for (int j = 0; j < C; j++) {
                    bool unb = ((j / width) % 2) == 0;
                    for (int i = 0; i < R; i++)
                        g[i][j] = unb ? '.' : '#';
                }
            }
            // place K on a random unburned
            vector<pair<int,int>> cells;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    if (g[i][j] == '.') cells.emplace_back(i, j);
            auto p = rnd.any(cells);
            g[p.first][p.second] = 'K';
        } else {
            // random burns
            R = rnd.wnext(8, -1);
            C = rnd.wnext(8, -1);
            R = max(R, 2);
            C = max(C, 2);
            double p = rnd.next(0.0, 1.0);
            g.assign(R, string(C, '.'));
            int kr = rnd.next(0, R-1), kc = rnd.next(0, C-1);
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (i == kr && j == kc) continue;
                    if (rnd.next() < p) g[i][j] = '#';
                }
            }
            g[kr][kc] = 'K';
        }
        println(R, C);
        for (auto &row : g)
            printf("%s\n", row.c_str());
    }
    return 0;
}
