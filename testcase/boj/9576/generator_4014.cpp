#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Number of books N and students M
        int N = rnd.next(1, 10);
        int M = rnd.next(1, min(20, N * 3));
        println(N, M);

        // Hyper-parameters for interval lengths
        int small_max_len = max(1, N / 3);
        int large_min_len = max(1, (2 * N + 2) / 3); // ceil(2N/3)
        bool can_large = (large_min_len <= N);

        for (int i = 0; i < M; i++) {
            // Choose a type of interval
            // 0: single-point, 1: small, 2: large, 3: full, 4: random
            int type = rnd.next(0, 4);
            if (type == 2 && !can_large) {
                // fallback if large not possible
                type = rnd.next(0, 1) ? 1 : 0;
            }

            int a, b;
            if (type == 0) {
                // single-point
                a = b = rnd.next(1, N);
            } else if (type == 1) {
                // small-range
                int L = rnd.next(1, small_max_len);
                a = rnd.next(1, N - L + 1);
                b = a + L - 1;
            } else if (type == 2) {
                // large-range
                int L = rnd.next(large_min_len, N);
                a = rnd.next(1, N - L + 1);
                b = a + L - 1;
            } else if (type == 3) {
                // full-range
                a = 1;
                b = N;
            } else {
                // fully random valid interval
                a = rnd.next(1, N);
                b = rnd.next(a, N);
            }

            println(a, b);
        }
    }

    return 0;
}
