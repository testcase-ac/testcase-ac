#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    // tb: bias for burger prices, td: bias for drink prices
    int tb = rnd.next(-4, 4);
    int td = rnd.next(-4, 4);
    // Probability to duplicate a previous price
    double dupProb = rnd.next(0.0, 1.0);

    vector<int> prices;
    prices.reserve(5);
    for (int i = 0; i < 5; ++i) {
        if (i > 0 && rnd.next() < dupProb) {
            // Duplicate a previous price to test equal-value handling
            int idx = rnd.next(0, (int)prices.size() - 1);
            prices.push_back(prices[idx]);
        } else {
            int x;
            if (i < 3) {
                // burger price in [100,2000] with bias tb
                x = rnd.wnext(1901, tb) + 100;
            } else {
                // drink price in [100,2000] with bias td
                x = rnd.wnext(1901, td) + 100;
            }
            prices.push_back(x);
        }
    }

    // Output five lines: three burgers, then two drinks
    for (int p : prices) {
        println(p);
    }

    return 0;
}
