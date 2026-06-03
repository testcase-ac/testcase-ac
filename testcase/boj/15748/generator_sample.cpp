#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int l = rnd.next(n + 1, 60);
    int mode = rnd.next(0, 5);

    if (mode == 4) {
        n = rnd.next(1, 5);
        l = rnd.next(900000, 1000000);
    }

    int r_b = rnd.next(1, mode == 4 ? 999999 : 30);
    int r_f = rnd.next(r_b + 1, mode == 4 ? 1000000 : 60);

    vector<int> positions;
    for (int x = 1; x < l; ++x) {
        positions.push_back(x);
    }
    shuffle(positions.begin(), positions.end());
    positions.resize(n);
    sort(positions.begin(), positions.end());

    vector<int> tastiness(n);
    int base = rnd.next(1, mode == 4 ? 1000000 : 20);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            tastiness[i] = base + i * rnd.next(1, 4);
        } else if (mode == 1) {
            tastiness[i] = base + (n - 1 - i) * rnd.next(1, 4);
        } else if (mode == 2) {
            tastiness[i] = base;
        } else if (mode == 3) {
            tastiness[i] = rnd.next(1, 30);
            if (i == rnd.next(0, n - 1)) {
                tastiness[i] = rnd.next(80, 200);
            }
        } else if (mode == 4) {
            tastiness[i] = (i % 2 == 0) ? 1000000 : rnd.next(1, 10);
        } else {
            tastiness[i] = rnd.next(1, 100);
        }
    }

    println(l, n, r_f, r_b);
    for (int i = 0; i < n; ++i) {
        println(positions[i], tastiness[i]);
    }

    return 0;
}
