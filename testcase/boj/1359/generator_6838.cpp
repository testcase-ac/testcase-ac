#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: sometimes minimal, sometimes maximal, else random
    int N;
    double dr = rnd.next();
    if (dr < 0.15) N = 2;
    else if (dr < 0.30) N = 8;
    else N = rnd.next(2, 8);

    // Hyper-parameter for M: sometimes minimal, sometimes maximal, else random in [1, N-1]
    int maxM = N - 1;
    double pm = rnd.next();
    int M;
    if (pm < 0.20) M = 1;
    else if (pm < 0.40) M = maxM;
    else M = rnd.next(1, maxM);

    // Hyper-parameter for K: sometimes minimal, sometimes equal to M, else random in [1, M]
    double pk = rnd.next();
    int K;
    if (pk < 0.30) K = 1;
    else if (pk < 0.60) K = M;
    else K = rnd.next(1, M);

    // Output a single test case
    println(N, M, K);

    return 0;
}
