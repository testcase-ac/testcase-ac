#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of transitions
    int n = rnd.next(1, 10);

    // Choose a pattern for v_i
    int type = rnd.next(0, 4);
    vector<long long> v(n);

    if (type == 0) {
        // Uniform small values
        for (int i = 0; i < n; i++)
            v[i] = rnd.next(1, 100);
    } else if (type == 1) {
        // Roughly increasing
        for (int i = 0; i < n; i++)
            v[i] = rnd.next(1, 10) + i * rnd.next(1, 5);
    } else if (type == 2) {
        // Common divisor pattern
        int g = rnd.next(1, 20);
        for (int i = 0; i < n; i++)
            v[i] = g * rnd.next(1, 10);
    } else if (type == 3) {
        // Prime speeds
        vector<long long> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97
        };
        for (int i = 0; i < n; i++)
            v[i] = rnd.any(primes);
    } else {
        // Large random values
        for (int i = 0; i < n; i++)
            v[i] = rnd.next(100000000, 1000000000);
    }

    // Occasionally shuffle to add disorder
    if (rnd.next() < 0.3)
        shuffle(v.begin(), v.end());

    // Output
    println(n);
    println(v);

    return 0;
}
