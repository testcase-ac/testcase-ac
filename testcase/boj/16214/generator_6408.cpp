#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(6, 12);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 5);
        int N, M;
        if (type == 0) {
            // Trivial N=1 case
            N = 1;
            M = rnd.next(1, 100);
        } else if (type == 1) {
            // Trivial M=1 case
            N = rnd.next(1, 1000000000);
            M = 1;
        } else if (type == 2) {
            // Both small
            N = rnd.next(1, 10);
            M = rnd.next(1, 10);
        } else if (type == 3) {
            // Large N, M is power of two
            N = rnd.next(1, 1000000000);
            int k = rnd.next(1, 29);
            M = int(1LL << k);
        } else if (type == 4) {
            // Fully random large
            N = rnd.next(1, 1000000000);
            M = rnd.next(1, 1000000000);
        } else {
            // Small N, medium M
            N = rnd.next(2, 5);
            M = rnd.next(100, 200);
        }
        println(N, M);
    }
    return 0;
}
