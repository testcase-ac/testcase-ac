#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 3);
        a.assign(n, rnd.next(1, 5));
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        long long start = rnd.next(n + 1, n + 30);
        for (int i = 0; i < n; ++i) {
            a.push_back(max(1LL, start - i));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 25);
        long long value = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                value = rnd.next(1, 20);
            }
            a.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        long long transformed = rnd.next(n + 1, n + 20);
        for (int i = 0; i < n; ++i) {
            transformed += rnd.next(-2, 3);
            if (transformed <= i) {
                transformed = i + 1;
            }
            a.push_back(transformed - i);
        }
    } else if (mode == 4) {
        n = rnd.next(5, 35);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(1, 5));
            } else if (bucket == 1) {
                a.push_back(rnd.next(6, 50));
            } else {
                a.push_back(rnd.next(1000000000LL - 50, 1000000000LL));
            }
        }
    } else {
        n = rnd.next(20, 60);
        long long cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-5, 8);
            cur = min(1000000000LL, max(1LL, cur));
            a.push_back(cur);
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
