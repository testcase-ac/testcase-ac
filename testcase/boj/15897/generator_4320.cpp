#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose test type for diversity
    // 0 = very small (hand-checkable), 1 = moderate, 2 = large
    vector<int> types = {0, 0, 1, 1, 2};
    int t = rnd.any(types);

    long long n;
    if (t == 0) {
        // very small, pick from a few interesting values
        vector<long long> smalls = {1, 2, 3, 5, 10};
        n = rnd.any(smalls);
    } else if (t == 1) {
        // moderate range
        n = rnd.next(11, 1000);
    } else {
        // large range, sometimes a boundary
        if (rnd.next(0, 3) == 0) {
            vector<long long> bounds = {1000000000LL, 999999937LL};
            n = rnd.any(bounds);
        } else {
            n = rnd.next(1000000, 1000000000);
        }
    }

    println(n);
    return 0;
}
