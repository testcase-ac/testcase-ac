#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampSize(int x) {
    return max(2, min(200, x));
}

int oddInRange(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x % 2 == 0) {
        if (x < hi) ++x;
        else --x;
    }
    return x;
}

int evenInRange(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x % 2 == 1) {
        if (x < hi) ++x;
        else --x;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 2;
    int m = 2;
    int mode = rnd.next(8);

    if (mode == 0) {
        vector<pair<int, int>> tiny = {
            {2, 2}, {2, 3}, {3, 2}, {3, 3}, {2, 4}, {4, 2}
        };
        tie(n, m) = rnd.any(tiny);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{2, 3, 4, 5});
        m = rnd.next(2, 200);
        if (rnd.next(2)) swap(n, m);
    } else if (mode == 2) {
        n = oddInRange(3, 199);
        m = rnd.next(2, 200);
    } else if (mode == 3) {
        n = evenInRange(2, 200);
        m = rnd.next(2, 200);
    } else if (mode == 4) {
        int side = rnd.next(2, 40);
        n = side;
        m = side;
    } else if (mode == 5) {
        n = rnd.next(2, 40);
        m = rnd.next(2, 40);
    } else if (mode == 6) {
        n = rnd.next(150, 200);
        m = rnd.next(150, 200);
    } else {
        vector<int> edges = {2, 3, 4, 5, 196, 197, 198, 199, 200};
        n = rnd.any(edges);
        m = rnd.any(edges);
    }

    n = clampSize(n);
    m = clampSize(m);
    println(n, m);
    return 0;
}
