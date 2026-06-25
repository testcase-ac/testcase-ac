#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(0, 6);
        k = rnd.next(1, min(8, max(1, n - 1)));
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        m = rnd.any(vector<int>{0, 1, 2, 29, 30});
        k = rnd.next(1, 8);
    } else if (mode == 2) {
        n = rnd.any(vector<int>{1, 2, 3, 29, 30});
        m = rnd.next(0, 30);
        k = rnd.next(1, 8);
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        m = rnd.next(0, 30);
        k = rnd.any(vector<int>{1, 8});
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        m = rnd.next(20, 30);
        k = rnd.next(1, 8);
    } else if (mode == 5) {
        n = rnd.next(1, 30);
        m = rnd.next(0, 5);
        k = rnd.next(1, 8);
    } else {
        n = rnd.next(1, 30);
        m = rnd.next(0, 30);
        k = rnd.next(1, 8);
    }

    println(n, m, k);
    return 0;
}
