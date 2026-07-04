#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int N = rnd.next(1, 10);
    vector<int> P;
    int M = rnd.next(1, 50);

    if (mode == 0) {
        N = 1;
        P.assign(N, 1);
        P[0] = rnd.next(1, 50);
        M = rnd.next(P[0], 50);
    } else if (mode == 1) {
        N = rnd.next(2, 10);
        P.assign(N, rnd.next(20, 50));
        P[0] = rnd.next(1, 5);
        int cheapNonZero = rnd.next(1, N - 1);
        P[cheapNonZero] = rnd.next(1, 8);
        M = rnd.next(min(P[0], P[cheapNonZero]), 50);
    } else if (mode == 2) {
        N = rnd.next(2, 10);
        P.assign(N, 1);
        int cheap = rnd.next(1, 6);
        for (int i = 0; i < N; ++i) P[i] = rnd.next(cheap, 50);
        P[N - 1] = cheap;
        if (N > 2 && rnd.next(0, 1)) P[rnd.next(1, N - 2)] = cheap;
        M = rnd.next(cheap, 50);
    } else if (mode == 3) {
        N = rnd.next(2, 10);
        P.assign(N, 1);
        int base = rnd.next(1, 10);
        for (int i = 0; i < N; ++i) P[i] = min(50, base + rnd.next(0, 3));
        int tiePrice = rnd.next(1, 8);
        int a = rnd.next(0, N - 1);
        int b = rnd.next(0, N - 1);
        P[a] = tiePrice;
        P[b] = tiePrice;
        M = rnd.next(tiePrice, min(50, tiePrice * rnd.next(1, 8) + rnd.next(0, tiePrice - 1)));
    } else if (mode == 4) {
        N = rnd.next(2, 10);
        P.assign(N, 1);
        for (int i = 0; i < N; ++i) P[i] = rnd.next(10, 50);
        int first = rnd.next(1, N - 1);
        P[first] = rnd.next(2, 12);
        P[0] = rnd.next(1, P[first]);
        M = rnd.next(P[0], min(50, P[first] + rnd.next(0, 15)));
    } else if (mode == 5) {
        N = rnd.next(2, 10);
        P.assign(N, 1);
        for (int i = 0; i < N; ++i) P[i] = rnd.next(1, 50);
        int affordable = rnd.next(0, N - 1);
        P[affordable] = rnd.next(1, 10);
        M = rnd.next(P[affordable], min(50, P[affordable] + rnd.next(0, 5)));
    } else {
        N = rnd.next(1, 10);
        P.assign(N, 1);
        int minPrice = 51;
        for (int i = 0; i < N; ++i) {
            P[i] = rnd.next(1, 50);
            minPrice = min(minPrice, P[i]);
        }
        M = rnd.next(minPrice, 50);
    }

    println(N);
    println(P);
    println(M);
    return 0;
}
