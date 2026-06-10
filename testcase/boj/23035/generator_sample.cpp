#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX_COORD = 1000000000;

void addPoint(vector<pair<int, int>>& cats, set<pair<int, int>>& seen, int r,
              int c) {
    if (seen.emplace(r, c).second) cats.push_back({r, c});
}

int nearUpper(int limit) {
    if (limit == MAX_COORD) return MAX_COORD;
    return rnd.next(limit + 1, min(MAX_COORD, limit + 20));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(0, 30);
    int m = rnd.next(0, 30);

    if (mode == 4) {
        n = rnd.next(0, 1) ? MAX_COORD : rnd.next(0, 5);
        m = rnd.next(0, 1) ? MAX_COORD : rnd.next(0, 5);
    } else if (mode == 5) {
        if (rnd.next(0, 1)) n = 0;
        if (rnd.next(0, 1)) m = 0;
    }

    vector<pair<int, int>> cats;
    set<pair<int, int>> seen;

    if (mode == 0) {
        int t = rnd.next(0, 1);
        if (t == 1) addPoint(cats, seen, rnd.next(0, min(MAX_COORD, n + 1)),
                             rnd.next(0, min(MAX_COORD, m + 1)));
    } else if (mode == 1) {
        int t = rnd.next(3, 18);
        int lastR = 0, lastC = 0;
        for (int i = 0; i < t; ++i) {
            lastR = min(n, lastR + rnd.next(0, 3));
            lastC = min(m, lastC + rnd.next(0, 3));
            addPoint(cats, seen, lastR, lastC);
        }
    } else if (mode == 2) {
        int limit = min({n, m, 21});
        int t = rnd.next(1, max(1, limit + 1));
        for (int i = 0; i < t; ++i) {
            int r = i;
            int c = limit - i;
            addPoint(cats, seen, r, c);
        }
    } else if (mode == 3) {
        int t = rnd.next(8, 35);
        for (int i = 0; i < t; ++i) {
            int r = rnd.next(0, n);
            int c = rnd.next(0, m);
            addPoint(cats, seen, r, c);
            if (rnd.next(0, 2) == 0) addPoint(cats, seen, nearUpper(n), c);
            if (rnd.next(0, 2) == 0) addPoint(cats, seen, r, nearUpper(m));
        }
    } else {
        int t = rnd.next(5, 45);
        for (int i = 0; i < t; ++i) {
            int r, c;
            if (rnd.next(0, 3) == 0) {
                r = nearUpper(n);
                c = rnd.next(0, min(MAX_COORD, m + 20));
            } else if (rnd.next(0, 2) == 0) {
                r = rnd.next(0, min(MAX_COORD, n + 20));
                c = nearUpper(m);
            } else {
                r = rnd.next(0, n);
                c = rnd.next(0, m);
            }
            addPoint(cats, seen, r, c);
        }
    }

    shuffle(cats.begin(), cats.end());

    println(n, m);
    println((int)cats.size());
    for (auto [r, c] : cats) println(r, c);

    return 0;
}
