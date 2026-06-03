#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int base = rnd.next(20, 2000);
        n = base + rnd.next(0, 1);
    } else if (mode == 2) {
        int exp = rnd.next(1, 29);
        int delta = rnd.next(-3, 3);
        n = max(1, (1 << exp) + delta);
    } else if (mode == 3) {
        n = rnd.next(900000000, 1000000000);
    } else if (mode == 4) {
        vector<int> anchors = {2, 3, 5, 8, 10, 100, 999, 100000, 999999937};
        n = rnd.any(anchors);
    } else {
        n = rnd.next(1, 1000000000);
    }

    println(n);
    return 0;
}
