#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with varied sizes
    int N;
    if (rnd.next(0, 4) == 0) {
        N = 2;
    } else if (rnd.next(0, 3) == 0) {
        N = rnd.next(3, 6);
    } else if (rnd.next(0, 3) == 0) {
        N = rnd.next(7, 15);
    } else {
        N = rnd.next(16, 30);
    }

    // Hyper-parameter scenarios for distances
    int scenario = rnd.next(0, 2);
    vector<int> d(N);
    if (scenario == 0) {
        // all small distances
        for (int i = 0; i < N; i++) {
            d[i] = rnd.next(1, 10);
        }
    } else if (scenario == 1) {
        // mix of small and large distances
        for (int i = 0; i < N; i++) {
            if (rnd.next(0, 1) == 0)
                d[i] = rnd.next(1, 100);
            else
                d[i] = rnd.next(10000, 100000);
        }
    } else {
        // one heavy segment, others small
        int heavy = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++) {
            if (i == heavy)
                d[i] = rnd.next(100000, 500000);
            else
                d[i] = rnd.next(1, 10);
        }
    }

    // Shuffle positions slightly to avoid fixed patterns
    if (N > 2 && rnd.next(0, 1) == 0) {
        int shift = rnd.next(1, N - 1);
        rotate(d.begin(), d.begin() + shift, d.end());
    }

    // Output
    println(N);
    for (int x : d) println(x);

    return 0;
}
