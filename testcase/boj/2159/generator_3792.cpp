#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXC = 20;
    int N = rnd.next(1, 10);
    int scenario = rnd.next(0, 3);

    int sx = rnd.next(1, MAXC);
    int sy = rnd.next(1, MAXC);

    vector<pair<int,int>> pts;
    if (scenario == 0) {
        // linear path
        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        auto d = rnd.any(dirs);
        int dx = d.first, dy = d.second;
        int x = sx, y = sy;
        for (int i = 0; i < N; i++) {
            int step = rnd.next(1, 5);
            x += dx * step;
            y += dy * step;
            if (x < 1 || x > MAXC) {
                dx = -dx;
                x = min(max(x, 1), MAXC);
            }
            if (y < 1 || y > MAXC) {
                dy = -dy;
                y = min(max(y, 1), MAXC);
            }
            pts.emplace_back(x, y);
        }
    } else if (scenario == 1) {
        // random scattered
        for (int i = 0; i < N; i++) {
            int x = rnd.next(1, MAXC);
            int y = rnd.next(1, MAXC);
            pts.emplace_back(x, y);
        }
    } else if (scenario == 2) {
        // clusters
        int C = rnd.next(2, 4);
        vector<pair<int,int>> centers;
        for (int i = 0; i < C; i++) {
            centers.emplace_back(rnd.next(1, MAXC), rnd.next(1, MAXC));
        }
        int R = rnd.next(0, 5);
        for (int i = 0; i < N; i++) {
            auto c = rnd.any(centers);
            int dx = rnd.next(-R, R);
            int dy = rnd.next(-R, R);
            int x = c.first + dx;
            int y = c.second + dy;
            x = min(max(x, 1), MAXC);
            y = min(max(y, 1), MAXC);
            pts.emplace_back(x, y);
        }
    } else {
        // duplicates of a small seed set
        int S = rnd.next(1, min(N, 5));
        vector<pair<int,int>> seeds;
        for (int i = 0; i < S; i++) {
            seeds.emplace_back(rnd.next(1, MAXC), rnd.next(1, MAXC));
        }
        for (int i = 0; i < N; i++) {
            pts.push_back(rnd.any(seeds));
        }
    }

    // output
    println(N);
    println(sx, sy);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
