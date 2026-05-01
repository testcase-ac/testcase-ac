#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int W = rnd.next(1, 15);
    println(W);
    for (int i = 0; i < W; i++) {
        int type = rnd.next(0, 6);
        int p, q, n;
        switch (type) {
            case 0:
                // Small random values
                p = rnd.next(1, 10);
                q = rnd.next(1, 10);
                n = rnd.next(1, 10);
                break;
            case 1:
                // q = 1 edge case
                q = 1;
                p = rnd.next(1, 1000000);
                n = rnd.next(1, 1000000);
                break;
            case 2:
                // n = 1 edge case
                n = 1;
                p = rnd.next(1, 1000000);
                q = rnd.next(1, 1000000);
                break;
            case 3:
                // p < q
                q = rnd.next(2, 1000000);
                p = rnd.next(1, q - 1);
                n = rnd.next(1, 1000000);
                break;
            case 4:
                // p > q
                p = rnd.next(2, 1000000);
                q = rnd.next(1, p - 1);
                n = rnd.next(1, 1000000);
                break;
            case 5:
                // p is a multiple of q
                q = rnd.next(1, 500000);
                {
                    int maxk = 1000000 / q;
                    int k = rnd.next(2, maxk);
                    p = q * k;
                }
                n = rnd.next(1, 1000000);
                break;
            case 6:
                // Large n
                n = rnd.next(900000, 1000000);
                p = rnd.next(1, 1000000);
                q = rnd.next(1, 1000000);
                break;
            default:
                p = 1; q = 1; n = 1;
        }
        println(p, q, n);
    }
    return 0;
}
