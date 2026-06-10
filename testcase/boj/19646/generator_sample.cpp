#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 16);
    } else {
        n = rnd.next(17, 40);
    }

    vector<int> w(n);
    if (mode == 0) {
        w[0] = rnd.next(1, 1000);
    } else if (mode == 1) {
        int value = rnd.next(1, 1000);
        fill(w.begin(), w.end(), value);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            w[i] = i + 1;
        }
        if (rnd.next(0, 1) == 1) {
            reverse(w.begin(), w.end());
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            w[i] = (i % 2 == 0) ? rnd.next(1, 3) : rnd.next(800, 1000);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(1, 1000);
        }
    }

    vector<int> remaining = w;
    int total = accumulate(remaining.begin(), remaining.end(), 0);
    vector<int> p;
    p.reserve(n);

    int choiceMode = rnd.next(0, 4);
    for (int step = 0; step < n; ++step) {
        int pick;
        if (choiceMode == 0) {
            pick = 1;
        } else if (choiceMode == 1) {
            pick = total;
        } else if (choiceMode == 2) {
            pick = (total + 1) / 2;
        } else {
            pick = rnd.next(1, total);
        }
        p.push_back(pick);

        int prefix = 0;
        for (int i = 0; i < n; ++i) {
            prefix += remaining[i];
            if (prefix >= pick) {
                total -= remaining[i];
                remaining[i] = 0;
                break;
            }
        }
    }

    println(n);
    println(w);
    println(p);

    return 0;
}
