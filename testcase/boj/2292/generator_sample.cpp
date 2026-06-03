#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long layerEnd(long long layer) {
    return 1 + 3 * layer * (layer - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    vector<int> candidates;

    int mode = rnd.next(5);
    if (mode == 0) {
        candidates.push_back(1);
        candidates.push_back(rnd.next(1, 20));
    } else if (mode == 1) {
        int layer = rnd.next(2, 20);
        long long end = layerEnd(layer);
        for (int delta = -2; delta <= 2; ++delta) {
            long long value = end + delta;
            if (1 <= value && value <= maxN) candidates.push_back((int)value);
        }
    } else if (mode == 2) {
        int layer = rnd.next(2, 18258);
        long long start = layerEnd(layer - 1) + 1;
        long long end = min<long long>(layerEnd(layer), maxN);
        long long span = end - start;
        long long offset = rnd.next(0, (int)min<long long>(span, 1000));
        candidates.push_back((int)(start + offset));
        candidates.push_back((int)(end - rnd.next(0, (int)min<long long>(span, 1000))));
    } else if (mode == 3) {
        candidates.push_back(rnd.next(1, maxN));
        candidates.push_back(rnd.wnext(maxN, 4) + 1);
    } else {
        candidates.push_back(maxN - rnd.next(0, 100000));
    }

    println(rnd.any(candidates));
    return 0;
}
