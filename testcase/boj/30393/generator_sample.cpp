#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int MOD = 998244353;

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a = {rnd.next(1, 40)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(1, 12);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        a.assign(n, 1);
        int largeIndex = rnd.next(0, n - 1);
        a[largeIndex] = rnd.next(2, 80);
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        int total = rnd.next(n, 180);
        a.assign(n, 1);
        int remaining = total - n;
        while (remaining > 0) {
            int add = rnd.next(1, remaining);
            a[rnd.next(0, n - 1)] += add;
            remaining -= add;
        }
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        a.assign(n, 1);
        int total = MOD - 1 - rnd.next(0, 30);
        int remaining = total - n;
        while (remaining > 0) {
            int add = rnd.next(1, remaining);
            a[rnd.next(0, n - 1)] += add;
            remaining -= add;
        }
    } else {
        n = rnd.next(10, 35);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 25);
        }
    }

    shuffle(a.begin(), a.end());
    long long sum = accumulate(a.begin(), a.end(), 0LL);

    vector<int> mCandidates;
    mCandidates.push_back(1);
    mCandidates.push_back(static_cast<int>(sum));
    if (sum >= 2) {
        mCandidates.push_back(2);
        mCandidates.push_back(static_cast<int>(sum - 1));
    }
    mCandidates.push_back(rnd.next(1, static_cast<int>(sum)));
    int m = rnd.any(mCandidates);

    println(n, m);
    println(a);

    return 0;
}
