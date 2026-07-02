#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_COUNT = 1000000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 12);
    if (mode == 2) n = rnd.next(3, 12);
    if (mode == 5) n = rnd.next(13, 30);
    if (mode == 6) n = 30;

    vector<long long> a(n + 1, 0);

    if (mode == 0) {
        n = 2;
        a[2] = rnd.next(0LL, 5LL);
    } else if (mode == 1) {
        int level = rnd.next(2, n);
        a[level] = 1LL << (level - 2);
        for (int i = 2; i < level; ++i) {
            a[i] = rnd.next(0LL, min(3LL, MAX_COUNT));
        }
    } else if (mode == 2) {
        int level = rnd.next(3, n);
        a[level] = max(0LL, (1LL << (level - 2)) - 1);
        for (int i = 2; i < level; ++i) {
            a[i] = 0;
        }
    } else if (mode == 3) {
        long long need = 2;
        for (int i = 2; i <= n; ++i) {
            long long take = rnd.next(0LL, min(need, 4LL));
            a[i] = take;
            need = (need - take) * 2;
            if (need <= 0) {
                for (int j = i + 1; j <= n; ++j) {
                    a[j] = rnd.next(0LL, 3LL);
                }
                break;
            }
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a[i] = 0;
            } else {
                a[i] = rnd.next(1LL, 8LL);
            }
        }
    } else if (mode == 5) {
        for (int i = 2; i <= n; ++i) {
            a[i] = rnd.next(0LL, rnd.next(0, 4) == 0 ? MAX_COUNT : 20LL);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            a[i] = rnd.next(0, 1) ? MAX_COUNT : rnd.next(0LL, 100LL);
        }
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        if (i > 2) printf(" ");
        printf("%lld", a[i]);
    }
    printf("\n");

    return 0;
}
