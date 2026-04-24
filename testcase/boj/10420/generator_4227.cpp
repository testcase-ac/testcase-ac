#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Special interesting values
    vector<int> specials = {1, 28, 59, 60, 365, 366, 730, 731, 10000};

    int N;
    // With some probability pick a special value
    if (rnd.next(0, 3) == 0) {
        N = rnd.any(specials);
    } else {
        // Otherwise pick a category: small, medium, or large
        int cat = rnd.next(0, 2);
        if (cat == 0) {
            // Small offsets: within first 10 days
            N = rnd.next(1, 10);
        } else if (cat == 1) {
            // Medium offsets: month-to-year scale
            N = rnd.next(11, 1000);
        } else {
            // Large offsets: up to the maximum
            N = rnd.next(1001, 10000);
        }
    }

    // Output a single test case: the desired day count
    println(N);

    return 0;
}
