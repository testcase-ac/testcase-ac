#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int type = rnd.next(1, 4);

    if (type == 1) {
        // Very small, easy-to-check cases
        vector<int> small = {1, 2, 3, 4, 5};
        n = rnd.any(small);
    } else if (type == 2) {
        // Hand-picked interesting values including extremes
        vector<int> special = {1, 2, 5, 6, 7, 10, 42, 99, 100, 997, 998, 999, 1000};
        n = rnd.any(special);
    } else if (type == 3) {
        // Uniform random over the entire range
        n = rnd.next(1, 1000);
    } else {
        // Biased towards extremes (very small or very large)
        vector<int> ts = {-3, -1, 1, 3};
        int t = rnd.any(ts);
        n = 1 + rnd.wnext(1000, t); // in [1, 1000]
    }

    println(n);
    return 0;
}
