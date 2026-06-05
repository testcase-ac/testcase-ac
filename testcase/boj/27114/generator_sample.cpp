#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampEnergy(long long value) {
    return int(max(1LL, min(1000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int A = 1, B = 1, C = 1, K = 1;

    if (mode == 0) {
        A = rnd.next(1, 30);
        B = rnd.next(1, 30);
        C = rnd.next(1, 30);
        K = rnd.next(1, 120);
    } else if (mode == 1) {
        A = 2 * rnd.next(1, 50);
        B = 2 * rnd.next(1, 50);
        C = 2 * rnd.next(1, 50);
        K = 2 * rnd.next(0, 80) + 1;
    } else if (mode == 2) {
        C = rnd.next(1, 80);
        A = rnd.next(1, 120);
        B = rnd.next(1, 120);
        K = clampEnergy(2LL * rnd.next(1, 80) * C);
    } else if (mode == 3) {
        A = rnd.next(1, 100);
        B = rnd.next(1, 100);
        C = rnd.next(1, 150);
        int turns = 4 * rnd.next(1, 35);
        K = clampEnergy(1LL * turns * rnd.any(vector<int>{A, B}));
    } else if (mode == 4) {
        A = rnd.next(1, 90);
        B = rnd.next(1, 90);
        C = rnd.next(1, 90);
        int left = rnd.next(0, 20);
        int right = rnd.next(0, 20);
        int backParity = ((left - right) % 4 + 4) % 4;
        int back = backParity / 2;
        if (backParity % 2 != 0) {
            right += 1;
            backParity = ((left - right) % 4 + 4) % 4;
            back = backParity / 2;
        }
        back += 2 * rnd.next(0, 12);
        if (left + right + back == 0) left = right = 1;
        K = clampEnergy(1LL * left * A + 1LL * right * B + 1LL * back * C);
    } else {
        A = rnd.next(900000, 1000000);
        B = rnd.next(900000, 1000000);
        C = rnd.next(900000, 1000000);
        K = rnd.next(900000, 1000000);
    }

    println(A, B, C, K);
    return 0;
}
