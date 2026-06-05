#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    vector<int> values;

    int t = rnd.next(1, 1000);
    values.reserve(t);

    vector<int> anchors = {1, 2, 3, maxN - 2, maxN - 1, maxN};
    for (int p = 1; p <= maxN; p <<= 1) {
        for (int delta = -2; delta <= 2; ++delta) {
            int x = p + delta;
            if (1 <= x && x <= maxN) {
                anchors.push_back(x);
            }
        }
        if (p > maxN / 2) {
            break;
        }
    }

    while ((int)values.size() < t) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            n = rnd.next(1, 12);
        } else if (mode == 1) {
            n = rnd.any(anchors);
        } else if (mode == 2) {
            int p = 1 << rnd.next(0, 29);
            int span = min(1000, maxN - p);
            n = p + rnd.next(0, span);
        } else if (mode == 3) {
            n = maxN - rnd.next(0, 1000000);
        } else {
            n = rnd.next(1, maxN);
        }

        values.push_back(n);
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (int n : values) {
        println(n);
    }

    return 0;
}
