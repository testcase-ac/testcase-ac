#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makePartitionableBase(int pairs, int lo, int hi) {
    vector<int> weights;
    for (int i = 0; i < pairs; ++i) {
        int w = rnd.next(lo, hi);
        weights.push_back(w);
        weights.push_back(w);
    }
    return weights;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> weights;

    if (mode == 0) {
        int n = rnd.next(3, 12);
        int w = rnd.next(1, 20);
        weights.assign(n, w);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 8);
        weights = makePartitionableBase(pairs, 1, 30);
        weights.push_back(rnd.next(1, 60));
    } else if (mode == 2) {
        int pairs = rnd.next(1, 10);
        weights = makePartitionableBase(pairs, 900, 1000);
        weights.push_back(rnd.next(1, 1000));
    } else if (mode == 3) {
        int n = rnd.next(3, 20);
        int lo = rnd.next(1, 25);
        int span = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) weights.push_back(rnd.next(lo, min(1000, lo + span)));
    } else if (mode == 4) {
        int n = rnd.next(3, 30);
        int step = rnd.next(1, 12);
        int start = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) weights.push_back(min(1000, start + i * step));
    } else {
        int pairs = rnd.next(30, 149);
        weights = makePartitionableBase(pairs, 1, 1000);
        weights.push_back(rnd.next(1, 1000));
    }

    shuffle(weights.begin(), weights.end());

    println((int)weights.size());
    println(weights);

    return 0;
}
