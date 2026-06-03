#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        vector<int> anchors = {1, 2, 3, 4, 5, 6, 7, 12, 18, 24, 30, 36};
        int base = rnd.any(anchors);
        n = max(1, min(1000000, base + rnd.next(-2, 2)));
    } else if (mode == 2) {
        n = rnd.next(13, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 10000);
    } else if (mode == 4) {
        n = rnd.next(10001, 1000000);
    } else {
        n = 1000000 - rnd.next(0, 20);
    }

    println(n);
    return 0;
}
