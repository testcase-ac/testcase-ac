#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    int n;
    long long k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int cur = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(1, 3);
        }
        k = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(20, 1000);
        }
        k = rnd.next(1LL, 1000000LL);
    } else if (mode == 2) {
        n = rnd.next(4, 30);
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            if (i + 1 < n) {
                if (rnd.next(0, 1) == 0) {
                    cur += rnd.next(1, 5);
                } else {
                    cur += rnd.next(10, 10000);
                }
            }
        }
        k = rnd.next(1LL, 1000000000000LL);
    } else if (mode == 3) {
        n = rnd.next(1, 25);
        int start = 1000000000 - n + 1 - rnd.next(0, 50);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i);
        }
        k = rnd.next(1LL, 1000000000000000000LL);
    } else if (mode == 4) {
        n = rnd.next(100, 1000);
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(1, 4);
        }
        k = rnd.next(1LL, 1000000000000000000LL);
    } else {
        n = rnd.next(2, 40);
        vector<int> candidates;
        int limit = rnd.next(n, 200000);
        for (int i = 1; i <= limit; ++i) {
            candidates.push_back(i);
        }
        shuffle(candidates.begin(), candidates.end());
        candidates.resize(n);
        sort(candidates.begin(), candidates.end());
        a = candidates;
        k = rnd.next(1LL, 1000000000000000000LL);
    }

    println(n, k);
    println(a);
    return 0;
}
