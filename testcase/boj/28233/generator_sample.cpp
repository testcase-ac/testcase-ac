#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 40);
    } else if (mode == 3) {
        n = rnd.next(99950, 100000);
    } else {
        n = rnd.next(1, 100);
    }

    int limit = 2 * n;
    int i;
    int j;

    if (mode == 0 || mode == 4) {
        i = rnd.next(1, limit);
        j = i;
    } else if (mode == 5) {
        i = rnd.any(vector<int>{1, n, n + 1, limit});
        j = rnd.any(vector<int>{1, n, n + 1, limit});
    } else if (mode == 6) {
        int base = rnd.next(1, n);
        i = 2 * base - 1;
        j = min(limit, i + 1);
        if (rnd.next(0, 1)) {
            swap(i, j);
        }
    } else {
        i = rnd.next(1, limit);
        j = rnd.next(1, limit);
    }

    println(n, i, j);
    return 0;
}
