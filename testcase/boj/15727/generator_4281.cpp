#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a max bound for L to create diversity
    vector<int> max_choices = {10, 20, 100, 1000000};
    int maxL = rnd.any(max_choices);

    // Strategy modes for different edge patterns
    // 0: very small L (1..5)
    // 1: any L in [1..maxL]
    // 2: L divisible by 5
    // 3: L not divisible by 5
    int mode = rnd.next(0, 3);
    int L;
    if (mode == 0) {
        L = rnd.next(1, min(5, maxL));
    } else if (mode == 1) {
        L = rnd.next(1, maxL);
    } else if (mode == 2) {
        int maxk = max(1, maxL / 5);
        int k = rnd.next(1, maxk);
        L = 5 * k;
    } else {
        do {
            L = rnd.next(1, maxL);
        } while (L % 5 == 0);
    }

    // Output the single test case
    println(L);
    return 0;
}
