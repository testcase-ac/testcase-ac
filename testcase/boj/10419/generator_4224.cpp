#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);

    // Choose a maximum d for diversity
    int Dmax = rnd.any(vector<int>{10, 20, 50, 100, 500, 1000, 10000});

    vector<int> ds;
    ds.reserve(T);
    for (int i = 0; i < T; i++) {
        // Choose a pattern for d
        int type = rnd.next(0, 4);
        int d;
        if (type == 0) {
            // Minimal edge case
            d = 1;
        } else if (type == 1) {
            // Maximal edge case
            d = Dmax;
        } else if (type == 2) {
            // Bias toward small values
            d = 1 + rnd.wnext(Dmax, -2);
        } else if (type == 3) {
            // Bias toward large values
            d = 1 + rnd.wnext(Dmax, 2);
        } else {
            // Uniform random
            d = rnd.next(1, Dmax);
        }
        ds.push_back(d);
    }

    // Shuffle to avoid order biases
    shuffle(ds.begin(), ds.end());

    // Output
    println(T);
    for (int d : ds) {
        println(d);
    }

    return 0;
}
