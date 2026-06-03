#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    vector<int> anchors = {0, 1, 2, 300299, 300300, 300301, maxN - 2, maxN - 1, maxN};

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        int base = rnd.any(anchors);
        n = base + rnd.next(-20, 20);
        n = max(0, min(maxN, n));
    } else if (mode == 2) {
        n = rnd.next(0, 1000);
    } else if (mode == 3) {
        n = maxN - rnd.next(0, 1000);
    } else {
        n = rnd.next(0, maxN);
    }

    println(n);
    return 0;
}
