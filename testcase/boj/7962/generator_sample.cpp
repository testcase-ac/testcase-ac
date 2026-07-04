#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 18);
    vector<long long> fuel(n), dist(n);

    if (mode == 0) {
        long long base = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            dist[i] = base + rnd.next(0, 3);
            fuel[i] = dist[i] + rnd.next(0, 3);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            dist[i] = rnd.next(1, 9);
            fuel[i] = rnd.next(0, 4);
        }
        int rich = rnd.next(0, n - 1);
        fuel[rich] += rnd.next(12, 35);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            dist[i] = rnd.next(1, 7);
            fuel[i] = max(0LL, dist[i] + rnd.next(-3, 3));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            dist[i] = (i % 2 == 0 ? rnd.next(1, 4) : rnd.next(6, 12));
            fuel[i] = (i % 2 == 0 ? rnd.next(5, 12) : rnd.next(0, 3));
        }
    } else {
        n = rnd.next(8, 24);
        fuel.assign(n, 0);
        dist.assign(n, 1);
        int spikes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, n - 1);
            fuel[pos] += rnd.next(2, 10);
        }
    }

    if (rnd.next(0, 1) == 1) {
        int shift = rnd.next(0, n - 1);
        rotate(fuel.begin(), fuel.begin() + shift, fuel.end());
        rotate(dist.begin(), dist.begin() + shift, dist.end());
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(fuel[i], dist[i]);
    }

    return 0;
}
