#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int m;
    int n;

    if (mode == 0) {
        m = rnd.next(2, 6);
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        m = rnd.next(2, 20);
        int k = rnd.next(1, 12);
        n = min(10000, m * k);
    } else if (mode == 2) {
        m = rnd.next(2, 40);
        int k = rnd.next(1, 12);
        int delta = rnd.any(vector<int>{-1, 1});
        n = max(1, min(10000, m * k + delta));
    } else if (mode == 3) {
        m = rnd.next(20, 100);
        n = rnd.next(1, m - 1);
    } else if (mode == 4) {
        m = rnd.next(2, 100);
        n = rnd.next(m, min(10000, m + 80));
    } else if (mode == 5) {
        m = rnd.any(vector<int>{2, 3, 5, 10, 50, 100});
        n = rnd.next(9000, 10000);
    } else if (mode == 6) {
        m = rnd.next(2, 100);
        n = rnd.next(1, 10000);
    } else {
        m = 100;
        n = rnd.next(1, 10000);
    }

    println(n, m);
    return 0;
}
