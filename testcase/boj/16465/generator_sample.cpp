#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> widthsWithSum(int total, int preferredMaxN = 40) {
    int minN = (total + 2) / 3;
    int maxPossibleN = min(total, max(100, preferredMaxN));
    int compactMaxN = min(total, preferredMaxN);
    if (compactMaxN < minN) compactMaxN = maxPossibleN;
    int n = rnd.next(minN, compactMaxN);

    vector<int> widths(n, 1);
    int remaining = total - n;
    while (remaining > 0) {
        int i = rnd.next(0, n - 1);
        if (widths[i] == 3) continue;
        ++widths[i];
        --remaining;
    }
    shuffle(widths.begin(), widths.end());
    return widths;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m;
    int l;
    vector<int> widths;

    if (mode == 0) {
        int total = rnd.next(1, 120);
        widths = widthsWithSum(total);
        m = total;
        l = rnd.next(1, 300);
    } else if (mode == 1) {
        int mLimit = rnd.next(1, 180);
        int total = rnd.next(mLimit + 1, min(300, mLimit + 60));
        widths = widthsWithSum(total);
        m = mLimit;
        l = rnd.next(1, 300);
    } else if (mode == 2) {
        int total = rnd.next(1, 120);
        widths = widthsWithSum(total);
        m = rnd.next(total + 1, min(300, total + 80));
        l = rnd.next(1, total);
    } else if (mode == 3) {
        int total = rnd.next(1, 120);
        int gap = rnd.next(1, min(80, 300 - total));
        widths = widthsWithSum(total);
        m = total + gap;
        l = rnd.next(1, gap);
    } else if (mode == 4) {
        int total = rnd.next(1, 80);
        int maxL = min(300, total + 80);
        l = rnd.next(total + 1, maxL);
        int gap = rnd.next(1, min(l - 1, 300 - total));
        widths = widthsWithSum(total);
        m = total + gap;
    } else {
        int n = rnd.next(60, 100);
        widths.resize(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            widths[i] = rnd.next(1, 3);
            total += widths[i];
        }
        if (rnd.next(0, 1) == 0) {
            m = min(300, total);
        } else {
            m = rnd.next(max(1, total - 20), 300);
        }
        l = rnd.next(1, 300);
    }

    println((int)widths.size(), m, l);
    println(widths);

    return 0;
}
