#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to choose scenario: tight time, balanced, surplus time
    int scen = rnd.next(0, 2);
    int M, N;
    if (scen == 0) {
        M = rnd.next(1, 5);
        N = rnd.next(1, 2);
    } else if (scen == 1) {
        M = rnd.next(5, 15);
        N = rnd.next(2, 5);
    } else {
        M = rnd.next(10, 25);
        N = rnd.next(5, 20);
    }
    // Diversity hyper-parameters for a and b distributions
    double P_highA = rnd.next(0.0, 1.0);
    double P_highB = rnd.next(0.0, 1.0);
    vector<int> a(M), b(M);
    for (int i = 0; i < M; i++) {
        if (rnd.next() < P_highA) {
            // High base score
            a[i] = rnd.next(70, 100);
        } else {
            a[i] = rnd.next(1, 69);
        }
        if (rnd.next() < P_highB) {
            // High gain per hour
            b[i] = rnd.next(50, 100);
        } else {
            b[i] = rnd.next(1, 49);
        }
    }
    // Output
    println(N, M);
    println(a);
    println(b);
    return 0;
}
