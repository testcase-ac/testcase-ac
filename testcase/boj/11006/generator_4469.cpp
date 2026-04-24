#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        // Hyper-parameter for chicken count M
        int typeM = rnd.next(0, 2);
        int M;
        if (typeM == 0) {
            // small flocks
            M = rnd.next(1, 5);
        } else if (typeM == 1) {
            // medium flocks
            M = rnd.next(6, 50);
        } else {
            // large flocks
            M = rnd.next(51, 300);
        }
        // Determine valid range for total legs N: M ≤ N ≤ min(2*M,300)
        int nlow = M;
        int nhigh = min(2 * M, 300);
        // Hyper-parameter for leg-sum patterns
        double choice = rnd.next();
        int N;
        if (choice < 0.2) {
            // all chickens missing one leg
            N = nlow;
        } else if (choice < 0.4) {
            // all chickens healthy
            N = nhigh;
        } else {
            // general case
            N = rnd.next(nlow, nhigh);
        }
        // Output a test case
        println(N, M);
    }
    return 0;
}
