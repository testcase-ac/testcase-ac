#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of bettors (including Julia)
    int n = rnd.next(3, 10);

    // Julia's starting points (small for hand-checking)
    long long P0 = rnd.next(0, 20);

    // Prepare scores: Julia first, others not exceeding P0
    vector<long long> p(n);
    p[0] = P0;

    // Hyper-parameter for distribution: favor high, low, or uniform
    vector<int> weights = {-1, 0, 1};
    int t = rnd.any(weights);

    for (int i = 1; i < n; ++i) {
        // rnd.wnext(P0+1, t) generates 0..P0 with weighted bias
        p[i] = rnd.wnext(P0 + 1, t);
    }

    // Output in problem format
    println(n);
    println(p);

    return 0;
}
