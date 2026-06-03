#include "testlib.h"

#include <algorithm>

using namespace std;

int clampScore(int value) {
    return max(0, min(1000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A = 0;
    int P = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int k = rnd.next(0, 76);
        A = 13 * k;
        P = 7 * k;
    } else if (mode == 1) {
        P = rnd.next(0, 77);
        int tieA = 13 * P / 7;
        int delta = rnd.next(1, 5);
        A = clampScore(tieA + delta);
    } else if (mode == 2) {
        A = rnd.next(0, 142);
        int tieP = 7 * A / 13;
        int delta = rnd.next(1, 5);
        P = clampScore(tieP + delta);
    } else if (mode == 3) {
        const int edge[] = {0, 1, 7, 13, 76, 77, 142, 143, 999, 1000};
        A = edge[rnd.next(0, 9)];
        P = edge[rnd.next(0, 9)];
    } else {
        A = rnd.next(0, 1000);
        P = rnd.next(0, 1000);
    }

    println(A, P);
    return 0;
}
