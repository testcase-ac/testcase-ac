#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for A: sometimes corner values, sometimes small/medium/large random
    int A;
    double prob = rnd.next();
    if (prob < 0.2) {
        A = 1;                    // minimal corner
    } else if (prob < 0.4) {
        A = 9999;                 // maximal corner
    } else if (prob < 0.6) {
        A = rnd.next(2, 9);       // small two-digit–ish
    } else if (prob < 0.8) {
        A = rnd.next(10, 999);    // medium
    } else {
        A = rnd.next(1000, 9999); // large
    }

    // Hyper-parameter for P: uniform from 1 to 5
    int P = rnd.next(1, 5);

    // Output a single test case
    println(A, P);

    return 0;
}
