#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c = (mode == 0 ? 0 : rnd.next(1, 30));
    println(c);

    for (int i = 0; i < c; ++i) {
        int n = rnd.next(1, 50);
        int m = rnd.next(1, 50);
        int a;

        if (mode == 1) {
            n = rnd.next(1, 4);
            m = rnd.next(1, 4);
            a = rnd.next(1, 20);
        } else if (mode == 2) {
            a = rnd.next(1, n * m);
        } else if (mode == 3) {
            a = rnd.next(n * m + 1, 100000000);
        } else if (mode == 4) {
            if (rnd.next(0, 1) == 0) {
                n = 1;
                m = rnd.next(1, 50);
            } else {
                n = rnd.next(1, 50);
                m = 1;
            }
            a = rnd.next(1, 100000000);
        } else {
            n = rnd.any(std::vector<int>{1, 2, 49, 50});
            m = rnd.any(std::vector<int>{1, 2, 49, 50});
            int limit = n * m;
            a = rnd.next(0, 1) == 0 ? rnd.next(1, limit) : rnd.next(limit + 1, 100000000);
        }

        println(n, m, a);
    }

    return 0;
}
