#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int e = 0;
    int mode = rnd.next(8);

    if (mode == 0) {
        n = 1;
        e = rnd.next(0, 2);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        e = rnd.next(0, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        e = rnd.next(0, min(30, n + 5));
    } else if (mode == 3) {
        n = rnd.next(1, 500);
        e = 0;
    } else if (mode == 4) {
        n = rnd.next(1, 500);
        e = rnd.next(495, 500);
    } else if (mode == 5) {
        n = rnd.next(450, 500);
        e = rnd.next(0, 500);
    } else if (mode == 6) {
        n = rnd.next(1, 500);
        e = n;
    } else {
        vector<int> candidates = {1, 2, 3, 4, 5, 10, 25, 50, 112, 250, 499, 500};
        n = rnd.any(candidates);
        e = rnd.next(0, 500);
    }

    println(n, e);
    return 0;
}
