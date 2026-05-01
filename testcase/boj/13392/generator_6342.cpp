#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, medium, large
    int grp = rnd.next(0, 2);
    int N;
    if (grp == 0) {
        N = rnd.next(3, 10);
    } else if (grp == 1) {
        N = rnd.next(11, 50);
    } else {
        N = rnd.next(51, 100);
    }

    // Modes for generating patterns
    // 0: fully random
    // 1: S all '0's, T random
    // 2: S arithmetic mod 10, T random
    // 3: S random, T small shifts of S
    int mode = rnd.next(0, 3);

    string S(N, '0'), T(N, '0');
    if (mode == 0) {
        for (int i = 0; i < N; i++) {
            S[i] = char('0' + rnd.next(0, 9));
            T[i] = char('0' + rnd.next(0, 9));
        }
    } else if (mode == 1) {
        // S all zeros
        for (int i = 0; i < N; i++) {
            T[i] = char('0' + rnd.next(0, 9));
        }
    } else if (mode == 2) {
        // S is arithmetic progression mod 10
        int start = rnd.next(0, 9);
        int step = rnd.next(1, 9);
        for (int i = 0; i < N; i++) {
            S[i] = char('0' + (start + i * step) % 10);
            T[i] = char('0' + rnd.next(0, 9));
        }
    } else {
        // mode 3: S random, T small shift from S
        for (int i = 0; i < N; i++) {
            S[i] = char('0' + rnd.next(0, 9));
        }
        for (int i = 0; i < N; i++) {
            int delta = rnd.next(-3, 3);
            int v = (S[i] - '0' + delta + 10) % 10;
            T[i] = char('0' + v);
        }
    }

    // Output
    println(N);
    printf("%s\n", S.c_str());
    printf("%s\n", T.c_str());

    return 0;
}
