#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> randomHeights(int count, int maxHeight, bool includeMax) {
    vector<int> values(count);
    int pattern = rnd.next(0, 4);

    for (int i = 0; i < count; ++i) {
        if (pattern == 0) {
            values[i] = rnd.next(0, maxHeight);
        } else if (pattern == 1) {
            values[i] = rnd.next(0, 1) ? maxHeight : rnd.next(0, maxHeight);
        } else if (pattern == 2) {
            values[i] = rnd.next(0, 3) == 0 ? 0 : rnd.next(0, maxHeight);
        } else {
            int bucket = rnd.next(0, 5);
            values[i] = (maxHeight * bucket) / 5;
        }
    }

    if (includeMax) {
        values[rnd.next(count)] = maxHeight;
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int maxHeight = rnd.next(0, 30);

    vector<int> z;
    vector<int> p;

    if (mode == 0) {
        z = randomHeights(n, maxHeight, true);
        p = randomHeights(m, maxHeight, true);
    } else if (mode == 1) {
        int otherMax = rnd.next(0, 30);
        if (otherMax == maxHeight) {
            otherMax = maxHeight == 30 ? 29 : maxHeight + 1;
        }
        z = randomHeights(n, maxHeight, true);
        p = randomHeights(m, otherMax, true);
    } else if (mode == 2) {
        z.assign(n, 0);
        p.assign(m, 0);
    } else if (mode == 3) {
        maxHeight = rnd.next(1, 1000000);
        z = randomHeights(n, maxHeight, true);
        p = randomHeights(m, maxHeight, true);
    } else {
        n = rnd.next(1, 4);
        m = rnd.next(8, 20);
        maxHeight = rnd.next(1, 50);
        z = randomHeights(n, maxHeight, true);
        p = randomHeights(m, maxHeight, true);
    }

    println(n, m);
    println(z);
    println(p);

    return 0;
}
