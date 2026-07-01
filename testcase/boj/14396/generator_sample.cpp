#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;

    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(0, 10);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(0, min(2000, n * (n - 1) / 2));
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        m = rnd.next(0, 2000);
    } else if (mode == 3) {
        n = rnd.next(2, 80);
        int base = rnd.next(0, 1000) * 2;
        m = base + rnd.next(0, 1);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{2, 3, 4, 33, 1999, 2000});
        m = rnd.next(0, 2000);
    } else if (mode == 5) {
        n = rnd.next(1500, 2000);
        m = rnd.next(0, 40);
    } else if (mode == 6) {
        n = rnd.next(1500, 2000);
        m = rnd.next(1960, 2000);
    } else {
        n = rnd.next(2, 2000);
        m = rnd.any(vector<int>{0, 1, 2, 3, 1998, 1999, 2000});
    }

    println(n, m);
    return 0;
}
