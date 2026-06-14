#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8,
        15, 16, 17, 18, 19, 20,
        4996, 4997, 4998, 4999, 5000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
    } else if (mode == 2) {
        int base = rnd.next(1, 1250);
        n = 4 * base;
    } else if (mode == 3) {
        int base = rnd.next(0, 1249);
        n = 4 * base + 1;
    } else if (mode == 4) {
        int base = rnd.next(0, 1249);
        n = 4 * base + 2;
    } else {
        int base = rnd.next(0, 1249);
        n = 4 * base + 3;
    }

    println(n);
    return 0;
}
