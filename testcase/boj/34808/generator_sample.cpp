#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, k;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
        k = rnd.next(0, 30);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = 1;
        k = rnd.next(0, 30);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        k = rnd.next(0, 30);
    } else if (mode == 3) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 3);
        if (rnd.next(0, 1)) swap(n, m);
        k = 0;
    } else if (mode == 4) {
        n = rnd.any(vector<int>{1, 2, 999, 1000});
        m = rnd.any(vector<int>{1, 2, 999, 1000});
        k = rnd.any(vector<int>{0, 1, 1000000000});
    } else {
        n = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
        k = rnd.next(0, 1000000000);
    }

    println(n, m, k);
    return 0;
}
