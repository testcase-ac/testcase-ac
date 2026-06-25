#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    vector<int> a(n + 1, 0);

    if (mode == 0) {
        // Mostly empty boards, including the all-empty edge case.
        int blocks = rnd.next(0, min(n, 4));
        vector<int> positions;
        for (int i = 1; i <= n; ++i) {
            positions.push_back(i);
        }
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < blocks; ++i) {
            a[positions[i]] = rnd.next(2, n);
        }
    } else if (mode == 1) {
        // Dense boards with many standing blocks.
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 99) < 75) {
                a[i] = rnd.next(2, n);
            }
        }
    } else if (mode == 2) {
        // Alternating occupied and empty cells.
        int start = rnd.next(0, 1);
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == start) {
                a[i] = rnd.next(2, n);
            }
        }
    } else if (mode == 3) {
        // Heights close to nearby gaps, making tip feasibility borderline.
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 99) < 45) {
                int local = rnd.next(2, min(n, max(2, rnd.next(2, 8))));
                a[i] = local;
            }
        }
    } else if (mode == 4) {
        // A few very tall blocks near the ends and middle.
        vector<int> candidates = {1, 2, n / 2, (n + 1) / 2, n - 1, n};
        shuffle(candidates.begin(), candidates.end());
        int blocks = rnd.next(1, min<int>(candidates.size(), 5));
        for (int i = 0; i < blocks; ++i) {
            a[candidates[i]] = rnd.next(max(2, n - 5), n);
        }
    } else {
        // Random medium-density boards with a biased height range.
        int low = rnd.next(2, n);
        int high = rnd.next(low, n);
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 99) < rnd.next(20, 65)) {
                a[i] = rnd.next(low, high);
            }
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            putchar(' ');
        }
        printf("%d", a[i]);
    }
    putchar('\n');

    return 0;
}
