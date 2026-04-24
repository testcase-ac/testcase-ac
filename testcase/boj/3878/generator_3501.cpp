#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    const int XMAX = 1000;
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(1, 5);
        int m = rnd.next(1, 5);
        bool wantSep = rnd.next(0, 1);

        // choose a random line a*x + b*y + c = 0
        int a, b, c;
        do {
            a = rnd.next(-10, 10);
            b = rnd.next(-10, 10);
        } while (a == 0 && b == 0);
        c = rnd.next(-1000, 1000);
        auto side = [&](int x, int y) {
            return a * (ll)x + b * (ll)y + c;
        };

        vector<pair<int,int>> blacks, whites;
        set<pair<int,int>> used;

        // Helper to generate separable sets
        auto genSep = [&]() {
            blacks.clear(); whites.clear(); used.clear();
            int trials = 0;
            // blacks on side > 0
            while ((int)blacks.size() < n && trials < 10000) {
                int x = rnd.next(0, XMAX);
                int y = rnd.next(0, XMAX);
                if (side(x,y) <= 0) { trials++; continue; }
                if (used.insert({x,y}).second)
                    blacks.emplace_back(x,y);
            }
            // whites on side < 0
            while ((int)whites.size() < m && trials < 20000) {
                int x = rnd.next(0, XMAX);
                int y = rnd.next(0, XMAX);
                if (side(x,y) >= 0) { trials++; continue; }
                if (used.insert({x,y}).second)
                    whites.emplace_back(x,y);
            }
            return (int)blacks.size() == n && (int)whites.size() == m;
        };

        if (wantSep) {
            // Generate a separable test case
            if (!genSep()) {
                // fallback to random mixed if fail
                blacks.clear(); whites.clear(); used.clear();
                while ((int)blacks.size() < n) {
                    int x = rnd.next(0, XMAX), y = rnd.next(0, XMAX);
                    if (used.insert({x,y}).second)
                        blacks.emplace_back(x,y);
                }
                while ((int)whites.size() < m) {
                    int x = rnd.next(0, XMAX), y = rnd.next(0, XMAX);
                    if (used.insert({x,y}).second)
                        whites.emplace_back(x,y);
                }
            }
        } else {
            // Generate a non-separable test: start with separable, then flip one white
            if (genSep()) {
                int idx = rnd.next(0, m-1);
                // generate a new white on black side
                for (int it = 0; it < 10000; it++) {
                    int x = rnd.next(0, XMAX), y = rnd.next(0, XMAX);
                    if (side(x,y) > 0 && used.insert({x,y}).second) {
                        whites[idx] = {x, y};
                        break;
                    }
                }
            } else {
                // fallback to random mixed
                blacks.clear(); whites.clear(); used.clear();
                while ((int)blacks.size() < n) {
                    int x = rnd.next(0, XMAX), y = rnd.next(0, XMAX);
                    if (used.insert({x,y}).second)
                        blacks.emplace_back(x,y);
                }
                while ((int)whites.size() < m) {
                    int x = rnd.next(0, XMAX), y = rnd.next(0, XMAX);
                    if (used.insert({x,y}).second)
                        whites.emplace_back(x,y);
                }
            }
        }

        // shuffle points to avoid order bias
        shuffle(blacks.begin(), blacks.end());
        shuffle(whites.begin(), whites.end());

        // output test case
        println(n, m);
        for (auto &p : blacks) println(p.first, p.second);
        for (auto &p : whites) println(p.first, p.second);
    }
    return 0;
}
