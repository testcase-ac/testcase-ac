#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<int> s;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        for (int i = 0; i < m; ++i) {
            int upper = rnd.next(0, 3) == 0 ? 100 : max(1, n + 5);
            s.push_back(rnd.next(1, upper));
        }
    } else if (mode == 1) {
        vector<int> bases = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
        int base = rnd.any(bases);
        n = max(1, min(1000000, base + rnd.next(-2, 6)));
        m = rnd.next(1, 20);
        for (int i = 0; i < m; ++i) {
            int center = rnd.any(bases);
            int value = center + rnd.next(-3, 3);
            s.push_back(max(1, min(1000000, value)));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = rnd.next(n, min(100, n + 30));
        for (int i = 0; i < m; ++i) {
            s.push_back(rnd.next(1, n));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 80);
        int distinct = rnd.next(1, min(n, 25));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) {
            pool.push_back(rnd.next(1, n));
        }
        m = rnd.next(distinct, distinct + 30);
        for (int i = 0; i < m; ++i) {
            s.push_back(rnd.any(pool));
        }
    } else if (mode == 4) {
        n = rnd.next(900000, 1000000);
        m = rnd.next(1, 30);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1) == 0) {
                s.push_back(rnd.next(max(1, n - 100), n));
            } else {
                s.push_back(rnd.next(1, 1000000));
            }
        }
    } else {
        n = rnd.next(1, 40);
        m = rnd.next(1, 40);
        for (int i = 0; i < m; ++i) {
            if (i % 3 == 0) {
                s.push_back(rnd.next(n + 1, min(1000000, n + 1000)));
            } else {
                s.push_back(rnd.next(1, n));
            }
        }
    }

    shuffle(s.begin(), s.end());
    println(n, static_cast<int>(s.size()));
    println(s);

    return 0;
}
