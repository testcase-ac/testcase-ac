#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int k = 1;
    int left = 0;
    int right = 0;

    if (mode == 0) {
        n = rnd.next(1, 20);
        k = rnd.next(1, n);
        left = rnd.next(0, n - k);
    } else if (mode == 1) {
        k = rnd.next(1, 30);
        left = rnd.next(0, 30);
        right = left;
        n = left + k + right;
    } else if (mode == 2) {
        k = rnd.next(1, 250);
        left = k;
        right = rnd.next(0, 1000 - 2 * k);
        n = left + k + right;
    } else if (mode == 3) {
        k = rnd.next(1, 250);
        right = k;
        left = rnd.next(0, 1000 - 2 * k);
        n = left + k + right;
    } else if (mode == 4) {
        k = rnd.next(1, 333);
        left = k;
        right = k;
        n = 3 * k;
    } else if (mode == 5) {
        n = 1000;
        k = rnd.any(vector<int>{1, 2, 3, 499, 500, 999, 1000});
        left = rnd.any(vector<int>{0, 1, max(0, n - k - 1), n - k});
    } else {
        n = rnd.next(20, 1000);
        k = rnd.next(1, n);
        left = rnd.next(0, n - k);
    }

    println(n, k, left);
    return 0;
}
