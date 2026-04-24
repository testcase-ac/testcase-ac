#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N for hand-checkable cases
    int N = rnd.next(4, 10);

    // Prepare some "interesting" K values around edge cases
    vector<int> ks = {1, N/2, N/2 + 1, N - 1, N};
    for (auto &k : ks) {
        if (k < 1) k = 1;
        if (k > N) k = N;
    }

    // Randomly decide whether to pick a uniform K or one of the edge cases
    int mode = rnd.next(0, 1);
    int K;
    if (mode == 0) {
        K = rnd.next(1, N);
    } else {
        K = rnd.any(ks);
    }

    // Output the generated test case
    println(N);
    println(K);

    return 0;
}
