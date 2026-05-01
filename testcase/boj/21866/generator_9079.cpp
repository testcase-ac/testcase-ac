#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> maxs = {100, 100, 200, 200, 300, 300, 400, 400, 500};
    int totalCap = 0;
    for (int x : maxs) totalCap += x;

    auto genWithinMaxWithSum = [&](int S) {
        vector<int> res(9, 0);
        vector<int> suffixCap(10, 0);
        for (int i = 8; i >= 0; --i)
            suffixCap[i] = suffixCap[i + 1] + maxs[i];

        int remaining = S;
        for (int i = 0; i < 9; ++i) {
            int maxFuture = suffixCap[i + 1];
            int low = remaining - maxFuture;
            if (low < 0) low = 0;
            int high = remaining < maxs[i] ? remaining : maxs[i];
            if (low > high) low = high; // safety
            int val = (low == high) ? low : rnd.next(low, high);
            res[i] = val;
            remaining -= val;
        }
        return res;
    };

    int scenario = rnd.next(0, 5);
    vector<int> a(9, 0);

    if (scenario == 0) {
        // All zeros: none
        // a already zeros
    } else if (scenario == 1) {
        // Random none: sum < 100, all within max
        int S = rnd.next(0, 99);
        a = genWithinMaxWithSum(S);
    } else if (scenario == 2) {
        // Draw: exact sum 100, within max
        a = genWithinMaxWithSum(100);
    } else if (scenario == 3) {
        // Draw: random sum >= 100, within max
        int S = rnd.next(100, totalCap);
        a = genWithinMaxWithSum(S);
    } else if (scenario == 4) {
        // Hacker: exactly one hacked problem
        int hackedIdx = rnd.next(0, 8);
        for (int i = 0; i < 9; ++i) {
            if (i == hackedIdx) continue;
            a[i] = rnd.next(0, maxs[i]);
        }
        int extraMax = 1000 - maxs[hackedIdx];
        int extra = rnd.next(1, min(10, extraMax));
        a[hackedIdx] = maxs[hackedIdx] + extra;
    } else if (scenario == 5) {
        // Hacker: multiple hacked problems
        int h = rnd.next(2, 5);
        vector<int> idx(9);
        for (int i = 0; i < 9; ++i) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        vector<int> hacked(idx.begin(), idx.begin() + h);

        vector<bool> isHacked(9, false);
        for (int i : hacked) isHacked[i] = true;

        for (int i = 0; i < 9; ++i) {
            if (isHacked[i]) {
                int lo = maxs[i] + 1;
                int hi = 1000;
                a[i] = rnd.next(lo, hi);
            } else {
                a[i] = rnd.next(0, maxs[i]);
            }
        }
    }

    println(a);
    return 0;
}
