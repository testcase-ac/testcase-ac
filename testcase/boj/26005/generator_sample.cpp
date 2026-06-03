#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {1, 2, 3, 4, 5, 10, 31, 32, 33, 99, 100, 999, 1000};
    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        int base = rnd.next(1, 32);
        n = min(1000, base * base + rnd.next(-1, 1));
    } else if (mode == 3) {
        n = rnd.next(1, 500) * 2;
    } else if (mode == 4) {
        n = rnd.next(0, 499) * 2 + 1;
    } else {
        n = rnd.next(900, 1000);
    }

    println(n);
    return 0;
}
