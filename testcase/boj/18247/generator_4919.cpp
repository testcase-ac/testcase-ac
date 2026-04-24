#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Six scenarios for diversity
        int sc = rnd.next(0, 5);
        int N, M;
        switch (sc) {
            case 0:
                // General valid case: N > 12, M > 4
                N = rnd.next(13, 26);
                M = rnd.next(5, 9);
                break;
            case 1:
                // Edge valid case exactly 12,4
                N = 12;
                M = 4;
                break;
            case 2:
                // Invalid row only: N < 12
                N = rnd.next(1, 11);
                M = rnd.next(1, 9);
                break;
            case 3:
                // Invalid column only: M < 4
                N = rnd.next(1, 26);
                M = rnd.next(1, 3);
                break;
            case 4:
                // Both invalid: N < 12, M < 4
                N = rnd.next(1, 11);
                M = rnd.next(1, 3);
                break;
            case 5:
                // Extreme valid: maximum bounds
                N = 26;
                M = 9;
                break;
        }
        println(N, M);
    }

    return 0;
}
