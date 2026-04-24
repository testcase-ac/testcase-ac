#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Select a scenario for variability
    double scen = rnd.next();
    vector<int> maxes = {100, 1000, 10000, 100000};
    int mx = rnd.any(maxes);
    int N, K;
    if (scen < 0.1) {
        // trivial case: N == K
        N = rnd.next(0, mx);
        K = N;
    } else if (scen < 0.4) {
        // small forward walk only
        N = rnd.next(0, 20);
        K = rnd.next(N + 1, N + 20);
    } else if (scen < 0.7) {
        // forward with teleport opportunities
        N = rnd.next(1, mx);
        int maxk = min(mx, N * 4 + rnd.next(1, 20));
        K = rnd.next(N + 1, maxk);
    } else {
        // N > K, must walk backwards
        N = rnd.next(1, mx);
        if(rnd.next() < 0.1) {
          K = 0;
        } else {
          K = rnd.next(0, N - 1);
        }
    }

    // Output the single test case
    println(N, K);
    return 0;
}
