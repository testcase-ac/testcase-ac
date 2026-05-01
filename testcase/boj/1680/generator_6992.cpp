#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 6);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 12);
        int W = rnd.next(1, 20);

        // generate sorted unique distances
        vector<int> x(N);
        x[0] = rnd.next(0, 3);
        for (int i = 1; i < N; ++i) {
            x[i] = x[i-1] + rnd.next(1, 5);
        }

        // generate weights with varied distributions
        vector<int> w(N);
        int t = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        for (int i = 0; i < N; ++i) {
            if (W == 1) {
                w[i] = 1;
            } else {
                w[i] = rnd.wnext(W-1, t) + 1;  // in [1..W]
            }
        }
        // ensure at least one point with weight == W, to force immediate returns
        if (N > 0 && rnd.next(0, 1) == 0) {
            int j = rnd.next(0, N-1);
            w[j] = W;
        }

        // output this test case
        println(W, N);
        for (int i = 0; i < N; ++i) {
            println(x[i], w[i]);
        }
    }

    return 0;
}
