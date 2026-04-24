#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose N size bucket
    int nType = rnd.next(0, 2);
    int N;
    if (nType == 0)      N = rnd.next(1, 3);
    else if (nType == 1) N = rnd.next(4, 7);
    else                 N = rnd.next(8, 10);

    // Hyper-parameter: choose maximum P_i size
    int pType = rnd.next(0, 2);
    int maxP;
    if (pType == 0)      maxP = rnd.next(1, 20);
    else if (pType == 1) maxP = rnd.next(21, 100000);
    else                 maxP = rnd.next(100001, 1000000000);

    // Hyper-parameter: duplication pattern
    int dupType = rnd.next(0, 2);
    vector<int> P(N);

    if (dupType == 2) {
        // All piles equal
        int v = rnd.next(1, maxP);
        for (int i = 0; i < N; i++) P[i] = v;
    } else if (dupType == 1) {
        // Half piles equal, half random
        int v = rnd.next(1, maxP);
        int half = N / 2;
        for (int i = 0; i < half; i++) P[i] = v;
        for (int i = half; i < N; i++) P[i] = rnd.next(1, maxP);
    } else {
        // All random
        for (int i = 0; i < N; i++) P[i] = rnd.next(1, maxP);
    }

    // Shuffle to mix duplicate blocks
    shuffle(P.begin(), P.end());

    // Output
    println(N);
    println(P);

    return 0;
}
