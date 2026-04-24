#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Price of chicken
        int P = rnd.next(1, 1000);

        // Generate M (money) in three categories:
        // 0: M < P, 1: M multiple of P, 2: general M > P not multiple
        int type = rnd.next(0, 2);
        int M;
        if (type == 0) {
            // M < P
            if (P > 1)
                M = rnd.next(1, P - 1);
            else
                M = 1;
        } else if (type == 1) {
            // M = k * P
            int k = rnd.next(1, 20);
            M = k * P;
        } else {
            // M = k * P + r, with r in [1, P-1]
            int k = rnd.next(0, 19);
            if (P > 1) {
                int r = rnd.next(1, P - 1);
                M = k * P + r;
            } else {
                // P == 1, everything is multiple
                int k2 = rnd.next(1, 20);
                M = k2;
            }
        }
        // Safety: ensure at least 1
        if (M < 1) M = P;

        // F = coupons needed for a free chicken
        int F = rnd.next(2, 20);

        // C = coupons given per paid chicken, 1 <= C < F
        int C;
        if (rnd.next(0, 4) == 0) {
            C = 1;
        } else if (rnd.next(0, 4) == 0) {
            C = F - 1;
        } else {
            C = rnd.next(1, F - 1);
        }

        // Output this test case
        println(P, M, F, C);
    }

    return 0;
}
