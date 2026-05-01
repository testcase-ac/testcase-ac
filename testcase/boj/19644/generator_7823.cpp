#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Distance L between 1 and 20 for hand-checkable size
    int L = rnd.next(1, 20);
    // Machine gun range: sometimes small, sometimes covering all
    int M_L;
    if (rnd.next(0, 1) == 0) {
        M_L = rnd.next(1, L);
    } else {
        M_L = rnd.next(L, L + rnd.next(0, 5));
    }
    // Damage per meter
    int M_K = rnd.next(1, 10);
    // Number of mines, possibly a bit more than L
    int C_ammo = rnd.next(0, L + 2);

    // Prepare Z_i values
    // Choose a maximum health for zombies to vary intensities
    int opt1 = M_K * L;
    vector<int> options = { max(1, opt1 / 2), opt1, 50, 100 };
    int maxZ = rnd.next(1, rnd.any(options));

    vector<int> Z(L);
    for (int i = 0; i < L; i++) {
        // 10% chance of no zombie at this position
        if (rnd.next(0, 9) == 0) {
            Z[i] = 0;
        } else {
            Z[i] = rnd.next(1, maxZ);
        }
    }

    // Output format
    println(L);
    println(M_L, M_K);
    println(C_ammo);
    for (int x : Z) println(x);

    return 0;
}
