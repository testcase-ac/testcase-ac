#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int l;
    int n;
    int t;

    if (mode == 0) {
        l = rnd.next(5, 12);
        n = rnd.next(2, min(5, (l - 1 + 1) / 2));
        t = rnd.next(1, 2 * l);
    } else if (mode == 1) {
        l = rnd.next(20, 80);
        n = rnd.next(4, min(12, (l - 1 + 1) / 2));
        t = rnd.next(l, min(1000, 5 * l));
    } else if (mode == 2) {
        l = rnd.next(80, 200);
        n = rnd.next(8, min(25, (l - 1 + 1) / 2));
        t = rnd.next(1, 1000);
    } else if (mode == 3) {
        l = rnd.next(900, 1000);
        n = rnd.next(20, 100);
        t = rnd.next(800, 1000);
    } else {
        l = rnd.next(5, 1000);
        n = rnd.next(2, min(100, (l - 1 + 1) / 2));
        t = rnd.next(1, 1000);
    }

    int parity = rnd.next(0, 1);
    vector<int> positions;
    for (int s = 1; s < l; ++s) {
        if (s % 2 == parity) {
            positions.push_back(s);
        }
    }
    if ((int)positions.size() < n) {
        positions.clear();
        parity ^= 1;
        for (int s = 1; s < l; ++s) {
            if (s % 2 == parity) {
                positions.push_back(s);
            }
        }
    }

    shuffle(positions.begin(), positions.end());
    positions.resize(n);
    sort(positions.begin(), positions.end());

    vector<string> dirs(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            dirs[i] = (positions[i] < l / 2 ? "L" : "R");
        } else if (mode == 1) {
            dirs[i] = (i % 2 == 0 ? "R" : "L");
        } else if (mode == 2) {
            dirs[i] = (i < n / 2 ? "R" : "L");
        } else {
            dirs[i] = (rnd.next(0, 1) == 0 ? "L" : "R");
        }
    }

    println(l, n, t);
    for (int i = 0; i < n; ++i) {
        println(positions[i], dirs[i]);
    }

    return 0;
}
