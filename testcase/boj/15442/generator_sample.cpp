#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 30);
        int maxSteps = n * (n + 1) / 2;
        k = rnd.next(n, maxSteps);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        int maxSteps = n * (n + 1) / 2;
        vector<int> candidates = {1, n, maxSteps, maxSteps + 1, 900};
        k = min(900, max(1, rnd.any(candidates) + rnd.next(-2, 2)));
    } else if (mode == 2) {
        n = rnd.next(20, 30);
        k = rnd.next(501, 900);
    } else if (mode == 3) {
        vector<int> boundaryN = {1, 2, 3, 29, 30};
        n = rnd.any(boundaryN);
        k = rnd.next(1, 900);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        k = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(1, 13);
        int maxSteps = n * (n + 1) / 2;
        k = rnd.next(1, maxSteps);
    } else {
        n = rnd.next(1, 30);
        k = rnd.next(1, 900);
    }

    println(n, k);
    return 0;
}
