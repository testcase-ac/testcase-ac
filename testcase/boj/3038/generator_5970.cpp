#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We pick N with some edge-case emphasis:
    // 10% chance for N=1, 10% for N=2, 10% for N=15, otherwise uniform in [3,14].
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.2) {
        N = 2;
    } else if (p < 0.3) {
        N = 15;
    } else {
        N = rnd.next(3, 14);
    }

    // Output the single integer N
    println(N);
    return 0;
}
