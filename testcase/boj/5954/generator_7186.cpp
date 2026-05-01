#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: small, medium, or larger
    int modeN = rnd.next(1, 3);
    int N;
    if (modeN == 1) {
        N = rnd.next(1, 5);       // very small
    } else if (modeN == 2) {
        N = rnd.next(6, 20);      // medium
    } else {
        N = rnd.next(21, 50);     // larger but still hand-checkable
    }
    // Hyper-parameter for maximum coin value Vmax
    int modeV = rnd.next(1, 3);
    int Vmax;
    if (modeV == 1) {
        Vmax = rnd.next(5, 10);    // small values
    } else if (modeV == 2) {
        Vmax = rnd.next(50, 100);  // medium values
    } else {
        Vmax = rnd.next(500, 2000); // large values
    }
    // Probability of duplicating an existing coin value
    double pDup = rnd.next(0.0, 1.0);
    vector<int> coins;
    coins.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < pDup) {
            // duplicate an existing value
            coins.push_back(rnd.any(coins));
        } else {
            // fresh random value
            coins.push_back(rnd.next(1, Vmax));
        }
    }
    // Shuffle the coin list to avoid any ordering bias
    shuffle(coins.begin(), coins.end());
    // Output
    println(N);
    for (int x : coins) {
        println(x);
    }
    return 0;
}
