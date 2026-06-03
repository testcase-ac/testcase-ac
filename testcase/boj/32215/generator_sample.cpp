#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int m;
    int k;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        n = rnd.next(2, 10);
        m = rnd.next(1, 10);
        k = rnd.next(1, n - 1);
    } else if (mode == 1) {
        n = rnd.next(990, 1000);
        m = rnd.next(990, 1000);
        k = rnd.next(n - 10, n - 1);
    } else if (mode == 2) {
        n = rnd.next(2, 1000);
        m = rnd.next(1, 1000);
        k = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 1000);
        m = rnd.next(1, 1000);
        k = n - 1;
    } else if (mode == 4) {
        vector<int> anchors = {1, 2, 10, 999, 1000};
        n = rnd.next(2, 1000);
        m = rnd.any(anchors);
        k = rnd.next(1, n - 1);
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        m = rnd.next(900, 1000);
        k = rnd.next(1, n - 1);
    } else {
        n = rnd.next(2, 1000);
        m = rnd.next(1, 1000);
        k = rnd.next(1, n - 1);
    }

    println(n, m, k);
    return 0;
}
