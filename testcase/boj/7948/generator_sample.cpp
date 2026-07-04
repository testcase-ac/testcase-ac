#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeCase(int k, int mode) {
    vector<int> sheep(k);

    if (mode == 0) {
        int hi = rnd.next(0, 30);
        for (int& value : sheep) value = rnd.next(0, hi);
    } else if (mode == 1) {
        int start = rnd.next(0, 12);
        int step = rnd.next(0, 5);
        for (int i = 0; i < k; ++i) sheep[i] = min(100000, start + i * step);
    } else if (mode == 2) {
        int start = rnd.next(0, 12);
        int step = rnd.next(0, 5);
        for (int i = 0; i < k; ++i) sheep[i] = max(0, start + (k - 1 - i) * step);
    } else if (mode == 3) {
        int base = rnd.next(0, 20);
        for (int& value : sheep) value = base + rnd.next(0, 2);
        int spikes = rnd.next(1, max(1, k / 2));
        for (int i = 0; i < spikes; ++i) sheep[rnd.next(k)] = rnd.next(50, 100000);
    } else if (mode == 4) {
        for (int i = 0; i < k; ++i) sheep[i] = max(0, i + rnd.next(-2, 2));
        shuffle(sheep.begin(), sheep.end());
    } else {
        int lo = rnd.next(99970, 100000);
        for (int& value : sheep) value = rnd.next(lo, 100000);
    }

    if (rnd.next(0, 4) == 0) reverse(sheep.begin(), sheep.end());
    return sheep;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 12);
    int remainingK = rnd.next(z, 180);

    println(z);
    for (int tc = 1; tc <= z; ++tc) {
        int casesLeft = z - tc + 1;
        int maxK = min(35, remainingK - (casesLeft - 1));
        int k = (tc == z) ? remainingK : rnd.next(1, maxK);
        remainingK -= k;

        vector<int> sheep = makeCase(k, rnd.next(0, 5));

        printf("%d", k);
        for (int value : sheep) printf(" %d", value);
        printf("\n");
    }

    return 0;
}
