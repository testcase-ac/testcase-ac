#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;

    int mode = rnd.next(0, 5);
    int n = 1;
    long long l = 1;
    vector<long long> x;

    if (mode == 0) {
        n = 1;
        l = rnd.next(1LL, LIM);
        x.push_back(rnd.next(-LIM, LIM));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        l = rnd.next(1, 20);
        long long base = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            x.push_back(base + rnd.next(-l, l));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 24);
        l = rnd.next(1, 50);
        long long cur = rnd.next(-10000, -5000);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 3 * l + 10);
            x.push_back(cur);
        }
    } else if (mode == 3) {
        int clusters = rnd.next(2, 5);
        l = rnd.next(1, 100);
        for (int c = 0; c < clusters; ++c) {
            int cnt = rnd.next(2, 6);
            long long center = rnd.next(-100000, 100000);
            for (int i = 0; i < cnt; ++i) {
                x.push_back(center + rnd.next(-2 * l, 2 * l));
            }
        }
        n = int(x.size());
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        l = rnd.next(1LL, LIM);
        x.push_back(-LIM);
        x.push_back(LIM);
        while (int(x.size()) < n) {
            x.push_back(rnd.next(-LIM, LIM));
        }
    } else {
        n = rnd.next(20, 80);
        l = rnd.next(1, 1000000);
        long long base = rnd.next(-500000000LL, 500000000LL);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(-3LL * l, 3LL * l);
            x.push_back(max(-LIM, min(LIM, base + step)));
            if (rnd.next(0, 4) == 0) {
                base += rnd.next(-10LL * l, 10LL * l);
                base = max(-LIM, min(LIM, base));
            }
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(x.begin(), x.end());
    }

    println(n, l);
    println(x);

    return 0;
}
