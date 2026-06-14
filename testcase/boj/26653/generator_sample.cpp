#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        int limit = 1 << n;
        m = max(1, limit - rnd.next(0, min(limit - 1, 5)));
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        int limit = 1 << n;
        m = min(1000000000, limit + rnd.next(0, 5));
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        int limit = 1 << n;
        m = rnd.next(1, limit);
    } else if (mode == 4) {
        n = rnd.next(11, 20);
        m = rnd.next(1, 2000);
    } else if (mode == 5) {
        n = 20;
        m = rnd.next(1048570, 1048585);
    } else if (mode == 6) {
        vector<int> values = {1, 2, 3, 10, 100, 1000, 1000000, 1000000000};
        n = rnd.next(1, 20);
        m = rnd.any(values);
    } else {
        n = rnd.next(1, 20);
        m = rnd.wnext(1000000000, rnd.next(-3, 3)) + 1;
    }

    println(n, m);
    return 0;
}
