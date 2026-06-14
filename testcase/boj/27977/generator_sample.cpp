#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(60, 120);
    } else {
        n = rnd.next(3, 24);
    }

    vector<int> gaps(n + 1, 1);

    if (mode == 0) {
        int extra = rnd.next(0, 40);
        for (int i = 0; i < extra; ++i) {
            gaps[rnd.next(0, n)]++;
        }
    } else if (mode == 1) {
        int bigGap = rnd.next(8, 80);
        int bigCount = rnd.next(1, min(n + 1, 4));
        for (int i = 0; i < bigCount; ++i) {
            gaps[rnd.next(0, n)] += bigGap + rnd.next(0, 20);
        }
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) {
            gaps[rnd.next(0, n)]++;
        }
    } else if (mode == 2) {
        for (int i = 0; i <= n; ++i) {
            gaps[i] = (i % 2 == 0 ? rnd.next(1, 3) : rnd.next(4, 25));
        }
    } else if (mode == 3) {
        int leftCluster = rnd.next(1, n - 1);
        for (int i = 0; i <= n; ++i) {
            if (i <= leftCluster) {
                gaps[i] = rnd.next(1, 3);
            } else {
                gaps[i] = rnd.next(5, 35);
            }
        }
    } else if (mode == 4) {
        int rightCluster = rnd.next(1, n - 1);
        for (int i = 0; i <= n; ++i) {
            if (i < rightCluster) {
                gaps[i] = rnd.next(5, 35);
            } else {
                gaps[i] = rnd.next(1, 3);
            }
        }
    } else {
        for (int i = 0; i <= n; ++i) {
            gaps[i] = rnd.next(1, 1000);
        }
    }

    int l = 0;
    for (int gap : gaps) {
        l += gap;
    }

    while (l < 5) {
        gaps[rnd.next(0, n)]++;
        l++;
    }

    int maxExtra = min(200000 - l, 300);
    if (maxExtra > 0 && rnd.next(0, 3) == 0) {
        int extra = rnd.next(1, maxExtra);
        for (int i = 0; i < extra; ++i) {
            gaps[rnd.next(0, n)]++;
        }
        l += extra;
    }

    vector<int> a;
    int position = 0;
    for (int i = 0; i < n; ++i) {
        position += gaps[i];
        a.push_back(position);
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = rnd.next(0, min(n, 3));
    } else if (kMode == 3) {
        k = rnd.next(max(0, n - 3), n);
    } else {
        k = rnd.next(0, n);
    }

    println(l, n, k);
    println(a);

    return 0;
}
