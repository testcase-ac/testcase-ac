#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of keys to generate
    int t = rnd.next(7, 10);

    // Starter special keys to cover edge and known-collision cases
    vector<long long> keys = {1, 2, 3, 11, 123456, 178800};

    // Fill remaining slots with diverse random keys
    while ((int)keys.size() < t) {
        int region = rnd.next(0, 2);
        long long k;
        if (region == 0) {
            // Small keys [1..1000]
            k = rnd.next(1LL, 1000LL);
        } else if (region == 1) {
            // Medium keys [1001..1e9]
            k = rnd.next(1001LL, 1000000000LL);
        } else {
            // Large keys [1e12..1e15]
            k = rnd.next(1000000000000LL, 1000000000000000LL);
        }
        keys.push_back(k);
    }

    // Shuffle to avoid any ordering bias
    shuffle(keys.begin(), keys.end());

    // Output
    println(t);
    for (auto k : keys)
        println(k);

    return 0;
}
