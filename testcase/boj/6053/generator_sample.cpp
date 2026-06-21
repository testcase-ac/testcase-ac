#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long clampHeight(long long x) {
    return max(1LL, min(1000000000LL, x));
}

void appendRun(vector<long long>& h, int len, long long& cur, int dir, int maxStep, bool allowFlat) {
    for (int i = 0; i < len; ++i) {
        int step = rnd.next(allowFlat ? 0 : 1, maxStep);
        cur = clampHeight(cur + dir * 1LL * step);
        h.push_back(cur);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 45);
    if (rnd.next(0, 9) == 0) n = rnd.next(80, 180);

    vector<long long> h;
    h.reserve(n);

    if (mode == 0) {
        long long cur = rnd.next(1, 1000);
        int dir = rnd.next(0, 1) == 0 ? -1 : 1;
        int maxStep = rnd.next(0, 25);
        h.push_back(cur);
        appendRun(h, n - 1, cur, dir, maxStep, true);
    } else if (mode == 1) {
        long long cur = rnd.next(1, 1000000);
        h.push_back(cur);
        int upLen = rnd.next(0, n - 1);
        int peakLen = rnd.next(1, n - upLen);
        int downLen = n - upLen - peakLen;

        appendRun(h, upLen, cur, 1, rnd.next(1, 40), true);
        long long peak = cur;
        for (int i = 1; i < peakLen; ++i) h.push_back(peak);
        cur = peak;
        appendRun(h, downLen, cur, -1, rnd.next(1, 40), true);
    } else if (mode == 2) {
        long long lo = rnd.next(1, 200);
        long long hi = rnd.next(999999800, 1000000000);
        for (int i = 0; i < n; ++i) {
            h.push_back(i % 2 == 0 ? hi - rnd.next(0, 20) : lo + rnd.next(0, 20));
        }
    } else if (mode == 3) {
        long long cur = rnd.next(10, 500);
        h.push_back(cur);
        while ((int)h.size() < n) {
            int dir = rnd.next(0, 1) == 0 ? -1 : 1;
            int len = min(n - (int)h.size(), rnd.next(1, 8));
            appendRun(h, len, cur, dir, rnd.next(0, 30), true);
        }
    } else if (mode == 4) {
        long long cur = rnd.next(1, 1000000000);
        int block = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) cur = rnd.next(1, 1000000000);
            h.push_back(cur);
        }
    } else {
        long long cur = rnd.next(1, 1000000000);
        h.push_back(cur);
        while ((int)h.size() < n) {
            int len = min(n - (int)h.size(), rnd.next(1, 10));
            int dir = rnd.next(0, 2) - 1;
            if (dir == 0) {
                for (int i = 0; i < len; ++i) h.push_back(cur);
            } else {
                appendRun(h, len, cur, dir, rnd.next(1, 1000000), true);
            }
        }
    }

    println((int)h.size());
    for (long long x : h) println(x);

    return 0;
}
