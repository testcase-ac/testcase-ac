#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long h = 0;
    vector<long long> a;

    if (mode == 0) {
        h = rnd.any(vector<long long>{0, 1, rnd.next(2LL, 1000000000LL)});
    } else {
        int n = 0;
        if (mode == 1) {
            h = rnd.next(2LL, 12LL);
            n = rnd.next(1, static_cast<int>(min<long long>(h - 1, 10)));
            for (int i = 0; i < n; ++i) {
                a.push_back(h - 1 - i);
            }
        } else if (mode == 2) {
            n = rnd.next(1, 8);
            h = rnd.next(1000000LL, 1000000000LL);
            long long cur = h;
            for (int i = 0; i < n; ++i) {
                long long remaining = n - i - 1;
                long long minDrop = 1;
                long long maxDrop = max(minDrop, (cur - 1 - remaining) / 2);
                cur -= rnd.next(minDrop, maxDrop);
                a.push_back(cur);
            }
        } else if (mode == 3) {
            h = rnd.next(20LL, 200LL);
            int n = rnd.next(2, static_cast<int>(min<long long>(h - 1, 12)));
            a.push_back(h - 1);
            long long cur = h - 1;
            for (int i = 1; i < n - 1; ++i) {
                long long remaining = n - i - 1;
                long long next = rnd.next(remaining + 1, cur - 1);
                a.push_back(next);
                cur = next;
            }
            a.push_back(1);
        } else {
            h = rnd.next(2LL, 200LL);
            int maxN = static_cast<int>(min<long long>(h - 1, 25));
            n = rnd.next(1, maxN);
            vector<long long> candidates;
            for (long long x = 1; x < h; ++x) {
                candidates.push_back(x);
            }
            shuffle(candidates.begin(), candidates.end());
            candidates.resize(n);
            sort(candidates.rbegin(), candidates.rend());
            a = candidates;
        }
    }

    println(static_cast<int>(a.size()), h);
    println(a);

    return 0;
}
