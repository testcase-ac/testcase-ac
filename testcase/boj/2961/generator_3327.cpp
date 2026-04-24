#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of ingredients
    int N = rnd.next(1, 10);

    // Determine a safe upper bound for sour tastes so that product <= 1e9, but keep small for hand-checking
    double dlim = pow(1e9, 1.0 / N);
    int limitS = max(1, int(dlim));
    limitS = min(limitS, 10);

    // Hyper-parameters to bias distribution of maxS and maxB
    vector<int> biases = {-2, -1, 0, 1, 2};
    int bS = rnd.any(biases);
    int bB = rnd.any(biases);

    // Choose max sourness and bitterness
    int maxS = rnd.wnext(limitS, bS) + 1;  // in [1..limitS]
    int maxB = rnd.wnext(10, bB) + 1;       // in [1..10]

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        int S = rnd.next(1, maxS);
        int B = rnd.next(1, maxB);
        println(S, B);
    }

    return 0;
}
