#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 2000000000;
    int mode = rnd.next(0, 7);
    int n = 0;

    if (mode == 0) {
        n = rnd.next(0, 20);
    } else if (mode == 1) {
        int bit = rnd.next(0, 30);
        n = 1 << bit;
    } else if (mode == 2) {
        int bit = rnd.next(1, 30);
        n = (1 << bit) - 1;
    } else if (mode == 3) {
        int bit = rnd.next(1, 30);
        int base = 1 << bit;
        int delta = rnd.next(-5, 5);
        n = clamp(base + delta, 0, MAX_N);
    } else if (mode == 4) {
        n = MAX_N - rnd.next(0, 1000);
    } else if (mode == 5) {
        n = 0;
        int bits = rnd.next(1, 8);
        vector<int> positions;
        for (int i = 0; i <= 30; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < bits; ++i) {
            int candidate = n | (1 << positions[i]);
            if (candidate <= MAX_N) n = candidate;
        }
    } else if (mode == 6) {
        n = rnd.next(0, MAX_N);
    } else {
        vector<int> anchors = {0, 1, 2, 3, 5, 7, 15, 31, 63, 127, 255, 1023, MAX_N};
        n = rnd.any(anchors);
    }

    println(n);
    return 0;
}
