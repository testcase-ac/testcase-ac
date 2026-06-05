#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 5);
    int mode = rnd.next(5);
    vector<int> counts(n, 1);

    if (mode == 0) {
        int hi = rnd.next(1, 4);
        for (int& count : counts) count = rnd.next(1, hi);
    } else if (mode == 1) {
        counts[0] = rnd.next(4, 10);
        for (int i = 1; i < n; ++i) counts[i] = rnd.next(1, 3);
    } else if (mode == 2) {
        int targetTotal = rnd.next(min(24, n * 10), min(35, n * 10));
        int remaining = targetTotal - n;
        while (remaining > 0) {
            int i = rnd.next(n);
            if (counts[i] == 10) continue;
            ++counts[i];
            --remaining;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) counts[i] = 1 + (i % 3);
        int extra = rnd.next(0, 8);
        while (extra-- > 0) {
            int i = rnd.next(n);
            if (counts[i] < 10) ++counts[i];
        }
    } else {
        int cap = rnd.next(10, 35);
        for (int i = 0; i < n; ++i) {
            int used = accumulate(counts.begin(), counts.end(), 0);
            int slotsLeft = n - i - 1;
            int maxHere = min(10, cap - used - slotsLeft);
            counts[i] = rnd.next(1, maxHere);
        }
    }

    shuffle(counts.begin(), counts.end());

    println(n);
    for (int count : counts) println(count);

    return 0;
}
