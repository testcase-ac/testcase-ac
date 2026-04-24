#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of children
    int N = rnd.next(1, 10);

    // Hyper-parameters for gaps
    vector<int> caps = {0, 1, 3, 5, 10};
    int capGap = rnd.any(caps);
    int bias = rnd.next(-2, 2);  // negative favors small diffs, positive favors large

    // Generate non-decreasing heights
    vector<int> h(N);
    h[0] = rnd.next(1, 5);
    for (int i = 1; i < N; i++) {
        int diff = rnd.wnext(capGap + 1, bias);
        h[i] = h[i-1] + diff;
    }

    // Number of groups
    int K = rnd.next(1, N);

    // Output
    println(N, K);
    println(h);

    return 0;
}
