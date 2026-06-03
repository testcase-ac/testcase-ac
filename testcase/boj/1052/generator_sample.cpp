#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N;
    int K;

    if (mode == 0) {
        N = rnd.next(1, 30);
        K = rnd.next(1, min(1000, N + 5));
    } else if (mode == 1) {
        int bits = rnd.next(1, 8);
        vector<int> positions;
        for (int i = 0; i < 24; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());

        N = 0;
        for (int i = 0; i < bits; ++i) N += 1 << positions[i];
        while (N > 10000000) N >>= 1;
        N = max(N, 1);
        K = rnd.next(1, min(1000, bits + 2));
    } else if (mode == 2) {
        int exponent = rnd.next(1, 23);
        int base = 1 << exponent;
        int delta = rnd.next(-min(20, base - 1), 20);
        N = min(10000000, max(1, base + delta));
        K = rnd.next(1, 20);
    } else if (mode == 3) {
        N = rnd.next(9990000, 10000000);
        K = rnd.next(1, 1000);
    } else if (mode == 4) {
        N = rnd.next(1, 10000000);
        K = rnd.next(1, 3);
    } else {
        N = rnd.next(1, 10000000);
        K = rnd.next(900, 1000);
    }

    println(N, K);
    return 0;
}
