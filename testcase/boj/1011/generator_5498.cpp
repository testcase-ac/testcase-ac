#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int cat = rnd.next(0, 3);
        long long d;
        if (cat == 0) {
            // small distance
            d = rnd.next(1, 10);
        } else if (cat == 1) {
            // medium distance
            d = rnd.next(11, 1000);
        } else if (cat == 2) {
            // near perfect squares
            long long k = rnd.next(2, 20);
            int offset = rnd.next(-1, 1);
            d = k * k + offset;
            if (d < 1) d = 1;
        } else {
            // large distance
            d = rnd.next(1000000000LL, 1000000100LL);
        }
        long long x = rnd.next(0, 1000);
        long long y = x + d;
        println(x, y);
    }
    return 0;
}
