#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;
    int m;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 5000000);
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(1, n);
        m = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = rnd.next(n + 1, 5000000);
        m = rnd.next(1, n);
    } else if (mode == 3) {
        n = rnd.next(10, 80);
        vector<int> ks = {1, 2, n - 1, n, n + 1, 2 * n + 1};
        k = min(5000000, rnd.any(ks));
        m = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.next(50, 500);
        k = rnd.next(1, min(5000000, 3 * n));
        m = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(1000, 20000);
        k = rnd.next(1, 5000000);
        m = rnd.next(1, n);
    } else if (mode == 6) {
        n = rnd.next(2, 5000000);
        k = rnd.next(1, 5000000);
        m = rnd.any(vector<int>{1, n, rnd.next(1, n)});
    } else {
        n = rnd.any(vector<int>{3, 99, 19999, 99999, 5000000});
        k = rnd.any(vector<int>{1, 2, 7, 11111, n, 5000000});
        m = rnd.any(vector<int>{1, min(3, n), (n + 1) / 2, n});
    }

    println(n, k, m);
    return 0;
}
