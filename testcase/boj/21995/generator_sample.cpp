#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void applyPairSwaps(vector<int>& p) {
    for (int i = 0; i + 1 < int(p.size()); i += 2) {
        swap(p[i], p[i + 1]);
    }
}

void applyHalfSwaps(vector<int>& p) {
    int n = int(p.size()) / 2;
    for (int i = 0; i < n; ++i) {
        swap(p[i], p[i + n]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 5) {
        n = rnd.next(25, 80);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> p(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        p[i] = i + 1;
    }

    if (mode == 0) {
        // Already sorted.
    } else if (mode == 1) {
        applyPairSwaps(p);
    } else if (mode == 2) {
        applyHalfSwaps(p);
    } else if (mode == 3) {
        int steps = rnd.next(2, min(2 * n, 20));
        bool pairTurn = rnd.next(0, 1);
        for (int step = 0; step < steps; ++step) {
            if (pairTurn) {
                applyPairSwaps(p);
            } else {
                applyHalfSwaps(p);
            }
            pairTurn = !pairTurn;
        }
    } else if (mode == 4) {
        int block = rnd.next(2, min(2 * n, 12));
        reverse(p.begin(), p.begin() + block);
        if (rnd.next(0, 1)) {
            reverse(p.end() - block, p.end());
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    println(n);
    println(p);

    return 0;
}
