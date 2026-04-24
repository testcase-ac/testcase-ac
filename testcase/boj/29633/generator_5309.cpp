#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to bias M towards small or large in [2,10]
    int t1 = rnd.next(-2, 2);
    int M = rnd.wnext(9, t1) + 2;  // rnd.wnext(9) -> [0,8], +2 -> [2,10]

    // K in [2, min(50, M+5)], with bias
    int maxK = min(50, M + 5);
    int t2 = rnd.next(-2, 2);
    int K = rnd.wnext(maxK - 1, t2) + 2;  // rnd.wnext(maxK-1)->[0,maxK-2], +2 -> [2,maxK]

    // Output the generated test case
    println(M);
    println(K);

    return 0;
}
