#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(1, 25);
    println(p);

    int startK = rnd.next(0, 1000000000 - p);
    int step = rnd.next(1, 17);

    for (int tc = 0; tc < p; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        int v;

        if (mode == 0) {
            n = rnd.next(2, 8);
            v = 0;
        } else if (mode == 1) {
            n = rnd.next(2, 8);
            v = n - 1;
        } else if (mode == 2) {
            n = rnd.next(2, 12);
            v = rnd.any(vector<int>{0, 1, n - 2, n - 1});
        } else if (mode == 3) {
            n = rnd.next(80, 100);
            v = rnd.next(0, n - 1);
        } else if (mode == 4) {
            n = rnd.next(2, 100);
            v = rnd.next(max(0, n / 2 - 3), min(n - 1, n / 2 + 3));
        } else {
            n = rnd.next(2, 100);
            v = rnd.next(0, n - 1);
        }

        int k = startK + tc * step;
        println(k, n, v);
    }

    return 0;
}
