#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for distribution bias: 0 = small-heavy, 1 = uniform, 2 = large-heavy
    int biasMissing = rnd.next(0, 2);
    int biasKnown   = rnd.next(0, 2);

    // Generator of a single book price in [1,10000] according to bias
    auto genPrice = [&](int bias) {
        if (bias == 1) {
            // uniform
            return rnd.next(1, 10000);
        } else if (bias == 0) {
            // small-heavy: take min of 4 samples
            return rnd.wnext(10000, -3) + 1;
        } else {
            // large-heavy: take max of 4 samples
            return rnd.wnext(10000, 3) + 1;
        }
    };

    // Generate missing price
    int missing = genPrice(biasMissing);

    // Generate known 9 prices
    vector<int> known(9);
    for (int i = 0; i < 9; i++) {
        known[i] = genPrice(biasKnown);
    }
    // Shuffle their order for variety
    shuffle(known.begin(), known.end());

    // Compute total for 10 books
    long long total = missing;
    for (int x : known) total += x;

    // Output format
    println(total);
    for (int x : known) {
        println(x);
    }

    return 0;
}
