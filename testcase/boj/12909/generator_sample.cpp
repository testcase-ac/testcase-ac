#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 6) {
        n = rnd.next(35, 51);
    } else {
        n = rnd.next(2, 14);
    }

    println(n);
    if (n == 1) {
        return 0;
    }

    vector<int> score(n);
    if (mode == 1) {
        int leaf = rnd.next(2000, 10000);
        score[1] = leaf;
        for (int d = 2; d < n; ++d) {
            score[d] = rnd.next(0, min(leaf, 2500));
        }
    } else if (mode == 2) {
        int peakDegree = rnd.next(max(1, n / 2), n - 1);
        for (int d = 1; d < n; ++d) {
            int distance = abs(d - peakDegree);
            score[d] = max(0, 10000 - distance * rnd.next(700, 1800) - rnd.next(0, 250));
        }
    } else if (mode == 3) {
        int start = rnd.next(0, 1500);
        int step = rnd.next(50, 600);
        for (int d = 1; d < n; ++d) {
            score[d] = min(10000, start + step * d + rnd.next(0, 120));
        }
    } else if (mode == 4) {
        int high = rnd.next(5000, 10000);
        for (int d = 1; d < n; ++d) {
            score[d] = rnd.next(0, 300);
        }
        int spikes = rnd.next(1, min(4, n - 1));
        for (int i = 0; i < spikes; ++i) {
            score[rnd.next(1, n - 1)] = rnd.next(high / 2, high);
        }
    } else if (mode == 5) {
        int center = rnd.next(1, n - 1);
        for (int d = 1; d < n; ++d) {
            score[d] = min(10000, abs(d - center) * rnd.next(300, 1200) + rnd.next(0, 400));
        }
    } else {
        int cap = rnd.next(20, 10000);
        for (int d = 1; d < n; ++d) {
            score[d] = rnd.next(0, cap);
        }
    }

    vector<int> output;
    for (int d = 1; d < n; ++d) {
        output.push_back(score[d]);
    }
    println(output);

    return 0;
}
