#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N, K;
    int type = rnd.next(0, 4);
    switch (type) {
        case 0:
            // N == K
            N = rnd.next(0, 100000);
            K = N;
            break;
        case 1:
            // N > K
            N = rnd.next(1, 100000);
            K = rnd.next(0, N - 1);
            break;
        case 2:
            // small positive difference
            N = rnd.next(0, 50);
            K = rnd.next(N + 1, min(N + 10, 100000));
            break;
        case 3:
            // medium positive difference
            N = rnd.next(0, 5000);
            K = rnd.next(N + 1, min(N + 2000, 100000));
            break;
        default:
            // fully random
            N = rnd.next(0, 100000);
            K = rnd.next(0, 100000);
    }
    println(N, K);
    return 0;
}
