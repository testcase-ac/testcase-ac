#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of points
    int N = rnd.next(3, 10);

    // Modes: 0 = all on a line, 1 = grid-like, 2 = random scatter
    int mode = rnd.next(0, 2);
    vector<pair<int,int>> pts;

    if (mode == 0) {
        // Line mode: either vertical or horizontal
        bool vertical = rnd.next(0,1);
        if (vertical) {
            int x0 = rnd.next(1, 20);
            for (int i = 1; i <= N; i++) {
                pts.emplace_back(x0, i);
            }
        } else {
            int y0 = rnd.next(1, 20);
            for (int i = 1; i <= N; i++) {
                pts.emplace_back(i, y0);
            }
        }
    }
    else if (mode == 1) {
        // Grid-like mode
        int kx = rnd.next(2, min(N, 5));
        int ky = rnd.next(2, min(N, 5));
        if (kx * ky < N) {
            ky = (N + kx - 1) / kx;
            if (ky < 2) ky = 2;
        }
        // generate simple xs = 1..kx, ys = 1..ky
        vector<int> xs, ys;
        for (int i = 1; i <= kx; i++) xs.push_back(i);
        for (int j = 1; j <= ky; j++) ys.push_back(j);
        // all combinations
        vector<pair<int,int>> all;
        for (int x : xs)
            for (int y : ys)
                all.emplace_back(x, y);
        shuffle(all.begin(), all.end());
        all.resize(N);
        pts = all;
    }
    else {
        // Random scatter mode
        set<pair<int,int>> S;
        while ((int)S.size() < N) {
            int x = rnd.next(1, 20);
            int y = rnd.next(1, 20);
            S.emplace(x, y);
        }
        for (auto &p : S) pts.push_back(p);
    }

    // Final shuffle and output
    shuffle(pts.begin(), pts.end());
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
