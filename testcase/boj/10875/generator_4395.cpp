#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: board half-size
    int L = rnd.next(1, 10);

    // Hyper-parameter: number of rotations, biased towards small
    int N = rnd.wnext(6, -2);  // yields in [0..5], bias to smaller

    vector<pair<int,char>> ops;
    for (int i = 0; i < N; ++i) {
        // Hyper-parameter: sometimes small t, sometimes relative to L
        int t;
        if (rnd.next() < 0.3) {
            t = rnd.next(1, 20);
        } else {
            t = rnd.next(1, 2 * L + 2);
        }
        char dir = rnd.any(string("LR"));
        ops.emplace_back(t, dir);
    }

    // Output
    println(L);
    println(N);
    for (auto &p : ops) {
        println(p.first, p.second);
    }

    return 0;
}
