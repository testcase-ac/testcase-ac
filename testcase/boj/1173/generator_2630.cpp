#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small exercise goal
    int N = rnd.next(1, 10);
    // Base and max heart rates
    int m = rnd.next(50, 99);
    int M = rnd.next(m + 1, 100);
    // Decide if it should be solvable
    bool solvable = rnd.next(0, 9) < 8;
    int T;
    if (solvable) {
        // Ensure at least one exercise minute is possible
        T = rnd.next(1, M - m);
    } else {
        // Make exercise impossible
        T = rnd.next(M - m + 1, 200);
    }
    // Recovery rate
    int R = rnd.next(1, 20);
    println(N, m, M, T, R);
    return 0;
}
