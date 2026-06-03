#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 10, 11, 27, 28, 81, 82, 999, 1000, 33332, 33333
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 1000);
    } else if (mode == 3) {
        int base = rnd.any(anchors);
        n = base + rnd.next(-3, 3);
        n = max(1, min(33333, n));
    } else if (mode == 4) {
        n = 33333 - rnd.next(0, 200);
    } else {
        n = rnd.next(1, 33333);
    }

    println(n);
    return 0;
}
