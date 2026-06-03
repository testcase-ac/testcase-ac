#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIMIT = 200000000;
    int K;
    int N;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        K = rnd.next(1, LIMIT);
        N = 1;
    } else if (mode == 1) {
        K = rnd.next(1, 1000);
        N = rnd.next(2, 10);
    } else if (mode == 2) {
        K = rnd.next(max(1, LIMIT - 1000), LIMIT);
        N = rnd.next(2, 10);
    } else if (mode == 3) {
        K = rnd.next(1, LIMIT);
        N = rnd.next(max(2, LIMIT - 1000), LIMIT);
    } else if (mode == 4) {
        K = rnd.next(1, LIMIT);
        N = rnd.next(2, 1000);
    } else if (mode == 5) {
        K = rnd.next(1, 1000);
        N = rnd.next(1000, LIMIT);
    } else {
        K = rnd.next(1, LIMIT);
        N = rnd.next(1, LIMIT);
    }

    println(K, N);
    return 0;
}
