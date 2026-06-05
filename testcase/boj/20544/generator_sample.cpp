#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        vector<int> anchors = {2, 3, 4, 5, 10, 20, 50, 100};
        int base = rnd.any(anchors);
        n = base + rnd.next(-1, 1);
    } else if (mode == 2) {
        n = rnd.next(9, 80);
    } else if (mode == 3) {
        n = rnd.next(81, 300);
    } else if (mode == 4) {
        n = rnd.next(301, 999);
    } else {
        n = 1000 - rnd.next(0, 20);
    }

    n = max(1, min(1000, n));
    println(n);

    return 0;
}
