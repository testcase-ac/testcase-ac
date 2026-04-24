#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate hyperparameters
    int N = rnd.next(1, 10);
    double valid_prob = rnd.next(0.0, 1.0);
    int ti_max = rnd.next(1, 50);
    int pi_max = rnd.next(1, 1000);

    vector<pair<int, int>> tp;

    for (int i = 1; i <= N; ++i) {
        int Ti;
        if (rnd.next(0.0, 1.0) < valid_prob) {
            // Generate valid Ti that fits within the remaining days
            int max_valid_t = N - i + 1;
            Ti = rnd.next(1, max_valid_t);
        } else {
            // Generate Ti up to ti_max, which might be invalid
            Ti = rnd.next(1, ti_max);
        }

        int Pi = rnd.next(1, pi_max);
        tp.emplace_back(Ti, Pi);
    }

    // Output the test case
    println(N);
    for (auto [t, p] : tp) {
        println(t, p);
    }

    return 0;
}
