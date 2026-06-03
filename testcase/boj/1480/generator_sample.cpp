#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int c;
    vector<int> w;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 3);
        c = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) w.push_back(rnd.next(1, 6));
    } else if (mode == 1) {
        n = rnd.next(3, 13);
        m = rnd.next(1, 10);
        c = 1;
        for (int i = 0; i < n; ++i) w.push_back(rnd.next(2, 20));
    } else if (mode == 2) {
        n = rnd.next(5, 13);
        m = rnd.next(1, 10);
        c = rnd.next(2, 20);
        int repeated = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                w.push_back(rnd.next(1, 20));
            } else {
                w.push_back(repeated);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(6, 13);
        m = rnd.next(2, 10);
        c = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                w.push_back(1);
            } else if (pick == 1) {
                w.push_back(c);
            } else if (pick == 2) {
                w.push_back(rnd.next(1, c));
            } else if (c < 20) {
                w.push_back(rnd.next(c + 1, 20));
            } else {
                w.push_back(20);
            }
        }
    } else if (mode == 4) {
        n = 13;
        m = rnd.next(1, 10);
        c = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) w.push_back(rnd.next(1, 20));
    } else {
        n = rnd.next(8, 13);
        m = rnd.next(6, 10);
        c = rnd.next(10, 20);
        for (int i = 0; i < n; ++i) {
            int lo = max(1, c / 2 - 2);
            int hi = min(20, c + 3);
            w.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(w.begin(), w.end());

    println(n, m, c);
    println(w);

    return 0;
}
