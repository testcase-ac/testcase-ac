#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int clampInt(int value, int lo, int hi) {
    return max(lo, min(value, hi));
}

int windowSum(const vector<int>& q, int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; ++i) sum += q[i];
    return sum;
}

void printCase(int n, int m, int t, const vector<int>& q, int p) {
    println(n, m, t);
    println(q);
    println(p);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    int t = 1;
    int p = 1;
    vector<int> q;

    if (mode == 0) {
        n = rnd.next(1, 4);
        t = rnd.next(1, 4);
        p = rnd.next(1, n);
        q.assign(n, 1);
        if (rnd.next(2)) {
            q[p - 1] = rnd.next(1, 20);
            m = rnd.next(1, q[p - 1]);
        } else {
            m = rnd.next(1, min(100000, accumulate(q.begin(), q.end(), 0) + 3));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        t = rnd.next(1, 8);
        p = rnd.next(1, n);
        q.resize(n);
        for (int& x : q) x = rnd.next(1, 12);

        int radius = rnd.next(0, min(t, max(p - 1, n - p)));
        int l = max(1, p - radius);
        int r = min(n, p + radius);
        m = windowSum(q, l - 1, r - 1);
        if (rnd.next(3) == 0) m = clampInt(m + rnd.next(-3, 3), 1, 100000);
    } else if (mode == 2) {
        n = rnd.next(6, 20);
        p = rnd.next(2, n - 1);
        q.resize(n);
        for (int& x : q) x = rnd.next(1, 25);

        int left = rnd.next(0, p - 1);
        int right = rnd.next(0, n - p);
        int travel = min(left, right) + left + right;
        t = clampInt(travel + rnd.next(0, 3), 1, 100);
        m = q[p - 1];
        for (int i = p - 1 - left; i <= p - 1 + right; ++i) {
            if (i != p - 1 && rnd.next(2)) m += q[i];
        }
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        p = rnd.next(2, n - 1);
        q.resize(n);
        for (int& x : q) x = rnd.next(1, 40);

        int farLeft = rnd.next(1, p - 1);
        int farRight = rnd.next(p + 1, n);
        int travel = min(p - farLeft, farRight - p) + (p - farLeft) + (farRight - p);
        t = clampInt(max(1, travel - rnd.next(1, 4)), 1, 100);
        m = q[p - 1] + q[farLeft - 1] + q[farRight - 1];
    } else if (mode == 4) {
        n = rnd.next(80, 100);
        p = rnd.next(1, n);
        t = rnd.next(80, 100);
        q.resize(n);
        for (int& x : q) x = rnd.next(900, 1000);
        int total = accumulate(q.begin(), q.end(), 0);
        m = rnd.next(max(1, total - 2000), 100000);
    } else {
        n = rnd.next(10, 35);
        p = rnd.next(1, n);
        t = rnd.next(1, 100);
        q.resize(n);
        int hi = rnd.any(vector<int>{3, 10, 100, 1000});
        for (int& x : q) x = rnd.next(1, hi);
        int total = accumulate(q.begin(), q.end(), 0);
        m = rnd.next(1, min(100000, total + rnd.next(0, 2000)));
    }

    printCase(n, m, t, q, p);
    return 0;
}
