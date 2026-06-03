#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 15, 16,
        31, 32, 63, 64, 127, 128,
        4997, 4998, 4999, 5000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        int base = rnd.any(anchors);
        n = max(1, min(5000, base + rnd.next(-1, 1)));
    } else if (mode == 2) {
        n = rnd.next(13, 80);
    } else if (mode == 3) {
        n = rnd.next(81, 500);
    } else if (mode == 4) {
        n = rnd.next(501, 2000);
    } else {
        n = rnd.next(2001, 5000);
    }

    println(n);
    return 0;
}
