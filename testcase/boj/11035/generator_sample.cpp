#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 20);
    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(3, 12);
            k = rnd.next(2, n - 1);
        } else if (mode == 1) {
            n = rnd.next(13, 80);
            k = rnd.next(2, n - 1);
        } else if (mode == 2) {
            n = rnd.next(81, 300);
            k = rnd.next(2, n - 1);
        } else if (mode == 3) {
            n = rnd.next(301, 1000);
            k = rnd.next(2, n - 1);
        } else if (mode == 4) {
            n = rnd.next(3, 1000);
            int window = rnd.next(1, 20);
            k = rnd.next(2, std::min(n - 1, window + 1));
        } else {
            n = rnd.next(3, 1000);
            int window = rnd.next(1, 20);
            k = rnd.next(std::max(2, n - window), n - 1);
        }

        println(n, k);
    }

    return 0;
}
