#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        vector<int> choices = {0, 1, n / 2, max(0, n - 1), n};
        k = rnd.any(choices);
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 12);
        k = 2 * rnd.next(0, n / 2);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 12) + 1;
        k = 2 * rnd.next(0, n / 2) + 1;
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(0, min(n, 5));
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        k = rnd.next(max(0, n - 5), n);
    } else {
        n = rnd.next(900000, 1000000);
        k = rnd.next(0, n);
    }

    println(n, k);
    return 0;
}
