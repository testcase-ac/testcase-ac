#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 2147483647LL;

    int mode = rnd.next(0, 5);
    int n = 1;
    long long m = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, 60LL));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        m = rnd.any(vector<long long>{2, 3, 5, 7, 10, 100, 1000, 1000000007LL});
        for (int i = 0; i < n; ++i) {
            long long base = rnd.next(1LL, min(2000LL, MAX_VALUE / m));
            long long value = base * m;
            if (rnd.next(0, 2) == 0 && value < MAX_VALUE) {
                value += rnd.next(1LL, min(m - 1, MAX_VALUE - value));
            }
            a.push_back(value);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        m = rnd.next(1000000000LL, MAX_VALUE);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 3);
            if (choice == 0) {
                a.push_back(MAX_VALUE - rnd.next(0LL, 1000LL));
            } else if (choice == 1) {
                a.push_back(m - rnd.next(0LL, min(1000LL, m - 1)));
            } else {
                a.push_back(rnd.next(1LL, 1000000LL));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        m = rnd.next(2LL, 100000LL);
        long long repeated = rnd.next(1LL, MAX_VALUE);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(repeated);
            } else {
                a.push_back(rnd.next(1LL, min(MAX_VALUE, repeated + 1000)));
            }
        }
    } else if (mode == 4) {
        n = 100;
        m = rnd.next(2LL, 1000000LL);
        long long lo = rnd.next(1LL, 1000LL);
        long long hi = rnd.next(lo, min(MAX_VALUE, lo + 100000LL));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else {
        n = rnd.next(1, 12);
        m = rnd.any(vector<long long>{1, MAX_VALUE, 2147483646LL, 1000000007LL});
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<long long>{1, 2, MAX_VALUE, MAX_VALUE - 1, rnd.next(1LL, MAX_VALUE)}));
        }
    }

    shuffle(a.begin(), a.end());

    println(n, m);
    println(a);

    return 0;
}
