#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(6, 12);
    println(caseCount);

    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = tc % 6;
        int n = rnd.next(1, 80);
        int m = rnd.next(1, min(n, 12));
        long long z = rnd.next(1, 1000);
        long long x = rnd.next(0, 1000);
        long long y = rnd.next(0, 1000);
        vector<long long> a(m);

        if (mode == 0) {
            n = rnd.next(1, 12);
            m = rnd.next(1, min(n, 6));
            z = rnd.next(1, 30);
            x = 0;
            y = 0;
            a.assign(m, 0);
            long long value = rnd.next(0, (int)z - 1);
            fill(a.begin(), a.end(), value);
        } else if (mode == 1) {
            n = rnd.next(5, 35);
            m = rnd.next(1, min(n, 10));
            z = rnd.next(m + 1, 200);
            x = 1;
            y = rnd.next(0, 5);
            a.assign(m, 0);
            for (int i = 0; i < m; ++i) {
                a[i] = i;
            }
        } else if (mode == 2) {
            n = rnd.next(8, 60);
            m = rnd.next(2, min(n, 12));
            z = rnd.next(2, 25);
            x = rnd.next(2, 50);
            y = rnd.next(0, 50);
            a.assign(m, 0);
            for (int i = 0; i < m; ++i) {
                a[i] = rnd.next(0, (int)z - 1);
            }
        } else if (mode == 3) {
            n = rnd.next(20, 120);
            m = rnd.next(1, min(n, 20));
            z = 1000000000LL;
            x = rnd.next(900000000, 1000000000);
            y = rnd.next(900000000, 1000000000);
            a.assign(m, 0);
            for (int i = 0; i < m; ++i) {
                a[i] = rnd.next(0, 1000000000 - 1);
            }
        } else if (mode == 4) {
            n = rnd.next(15, 90);
            m = rnd.next(1, min(n, 15));
            z = rnd.next(2, 100);
            x = rnd.next(0, 1);
            y = rnd.next(1, 20);
            a.assign(m, 0);
            for (int i = 0; i < m; ++i) {
                a[i] = (i % 3 == 0 ? 0 : rnd.next(0, (int)z - 1));
            }
        } else {
            n = rnd.next(70, 180);
            m = rnd.next(20, min(n, 100));
            z = rnd.next(50, 10000);
            x = rnd.next(0, 1000000000);
            y = rnd.next(0, 1000000000);
            a.assign(m, 0);
            for (int i = 0; i < m; ++i) {
                a[i] = rnd.next(0, (int)z - 1);
            }
        }

        println(n, m, x, y, z);
        for (long long value : a) {
            println(value);
        }
    }

    return 0;
}
