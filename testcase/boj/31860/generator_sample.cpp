#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(1, 5);
    int k = rnd.next(1, 3);
    int low = max(m, k) + 1;
    int mode = rnd.next(0, 5);
    int n;
    vector<int> d;

    if (mode == 0) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(low, min(1000, low + 2 * m + 3)));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int base = rnd.next(max(low, 980), 1000);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(max(low, base - 20), 1000));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        int value = rnd.next(low, 1000);
        d.assign(n, value);
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        int clusterCount = rnd.next(2, 5);
        vector<int> centers;
        for (int i = 0; i < clusterCount; ++i) {
            centers.push_back(rnd.next(low, 1000));
        }
        for (int i = 0; i < n; ++i) {
            int center = rnd.any(centers);
            int delta = rnd.next(-2 * m, 2 * m);
            d.push_back(min(1000, max(low, center + delta)));
        }
    } else {
        n = rnd.next(2, 40);
        int hi = rnd.next(low, 1000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                d.push_back(rnd.next(max(low, 950), 1000));
            } else {
                d.push_back(rnd.next(low, hi));
            }
        }
    }

    shuffle(d.begin(), d.end());

    println(n, m, k);
    for (int value : d) {
        println(value);
    }

    return 0;
}
