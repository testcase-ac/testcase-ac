#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int a, n, p;

        if (mode == 0) {
            a = rnd.next(1, 10);
            n = rnd.next(1, 10);
            p = rnd.next(1, 10);
        } else if (mode == 1) {
            p = rnd.next(1, 30);
            a = rnd.next(1, 5) * p;
            if (a > 100000) a = p;
            n = rnd.next(1, 20);
        } else if (mode == 2) {
            vector<int> moduli = {2, 3, 4, 5, 7, 8, 9, 11, 16, 25, 27, 32, 64, 81, 100};
            p = rnd.any(moduli);
            a = rnd.next(1, 1000);
            n = rnd.next(1, 100);
        } else if (mode == 3) {
            p = rnd.next(90000, 100000);
            a = rnd.next(90000, 100000);
            n = rnd.next(1, 25);
        } else if (mode == 4) {
            p = rnd.next(2, 100000);
            a = rnd.next(1, 100000);
            n = rnd.next(80, 100000);
        } else {
            p = rnd.next(1, 100000);
            a = rnd.next(1, 100000);
            n = rnd.next(1, 100000);
        }

        println(a, n, p);
    }

    return 0;
}
