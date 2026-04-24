#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<pair<int,int>> pts;
    int mode = rnd.next(0, 1);
    if (mode == 0) {
        // Grid mode: ensure at least one rectangle
        int r = rnd.next(2, 4);
        int c = rnd.next(2, 4);
        int dx = rnd.next(1, 3);
        int dy = rnd.next(1, 3);
        int x0 = rnd.next(0, 100 - (r - 1) * dx);
        int y0 = rnd.next(0, 100 - (c - 1) * dy);
        // choose two distinct rows and columns for guaranteed rectangle
        int i1 = rnd.next(0, r - 1), i2;
        do { i2 = rnd.next(0, r - 1); } while (i2 == i1);
        int j1 = rnd.next(0, c - 1), j2;
        do { j2 = rnd.next(0, c - 1); } while (j2 == j1);
        double keepProb = rnd.next();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                bool required = ( (i==i1||i==i2) && (j==j1||j==j2) );
                if (required || rnd.next() < keepProb) {
                    pts.emplace_back(x0 + i*dx, y0 + j*dy);
                }
            }
        }
    } else {
        // Random unique points mode
        int n = rnd.next(1, 10);
        set<pair<int,int>> st;
        while ((int)st.size() < n) {
            int x = rnd.next(0, 100);
            int y = rnd.next(0, 100);
            st.emplace(x, y);
        }
        for (auto &p : st) pts.push_back(p);
    }
    shuffle(pts.begin(), pts.end());
    println(pts.size());
    for (auto &p : pts) println(p.first, p.second);
    return 0;
}
