#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N-group: 0->N=1, 1->N=2, 2->N in [3,10]
    int tN = rnd.next(-1, 1);
    int Ngp = rnd.wnext(3, tN); // yields 0,1,2 with bias
    long long N;
    if (Ngp == 0) {
        N = 1;
    } else if (Ngp == 1) {
        N = 2;
    } else {
        N = rnd.next(3, 10);
    }
    // Generate M
    long long M;
    if (N >= 3) {
        // For N>=3, differentiate small/medium/large M
        int tM = rnd.next(-1, 1);
        int Mgp = rnd.wnext(3, tM);
        if (Mgp == 0) {
            M = rnd.next(1, 4);
        } else if (Mgp == 1) {
            M = rnd.next(5, 6);
        } else {
            M = rnd.next(7, 20);
        }
    } else {
        // For N=1 or 2, allow full range up to 20
        M = rnd.next(1, 20);
    }
    println(N, M);
    return 0;
}
