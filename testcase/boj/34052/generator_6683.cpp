#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Modes: 0=random yes-case, 1=boundary yes, 2=boundary no, 3=heavy no
    int mode = rnd.next(0, 3);
    int targetSum;
    const int MIN_SUM = 4;
    const int MAX_SUM = 4 * 1800;
    if (mode == 0) {
        // random yes-case: sum in [4,1500]
        targetSum = rnd.next(MIN_SUM, 1500);
    } else if (mode == 1) {
        // boundary yes-case: exactly 1500
        targetSum = 1500;
    } else if (mode == 2) {
        // boundary no-case: exactly 1501
        targetSum = 1501;
    } else {
        // heavy no-case: sum in [1502,7200]
        targetSum = rnd.next(1502, MAX_SUM);
    }
    vector<int> t(4);
    int sumAssigned = 0;
    for (int i = 0; i < 3; i++) {
        int partsLeft = 4 - i;
        int low = max(1, targetSum - sumAssigned - (partsLeft - 1) * 1800);
        int high = min(1800, targetSum - sumAssigned - (partsLeft - 1) * 1);
        t[i] = rnd.next(low, high);
        sumAssigned += t[i];
    }
    t[3] = targetSum - sumAssigned;
    // Shuffle to randomize lap order
    shuffle(t.begin(), t.end());
    // Output four lap times
    for (int x : t) println(x);
    return 0;
}
