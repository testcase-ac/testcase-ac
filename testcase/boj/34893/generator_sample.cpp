#include "testlib.h"

#include <algorithm>
#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxIngredient = 1000000000000000000LL;
    const array<long long, 8> anchors = {
        0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 1000000LL, kMaxIngredient
    };

    long long U = 0;
    long long O = 0;
    long long S = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        U = rnd.next(0LL, 20LL);
        O = rnd.next(0LL, 20LL);
        S = rnd.next(0LL, 20LL);
    } else if (mode == 1) {
        U = rnd.any(anchors);
        O = rnd.any(anchors);
        S = rnd.any(anchors);
    } else if (mode == 2) {
        S = rnd.next(0LL, 30LL);
        long long extra = rnd.next(0LL, 90LL);
        U = min(kMaxIngredient, S + extra);
        O = rnd.next(0LL, 60LL);
    } else if (mode == 3) {
        U = rnd.next(0LL, 60LL);
        S = rnd.next(U, min(kMaxIngredient, U + 60LL));
        O = rnd.next(0LL, 60LL);
    } else if (mode == 4) {
        U = rnd.next(0LL, 200LL);
        S = rnd.next(0LL, 200LL);
        O = rnd.next(0LL, 15LL);
    } else {
        long long base = rnd.next(kMaxIngredient - 1000LL, kMaxIngredient);
        U = base;
        S = rnd.next(max(0LL, base - 2000LL), kMaxIngredient);
        O = rnd.next(max(0LL, base - 2000LL), kMaxIngredient);
    }

    println(U, O, S);
    return 0;
}
