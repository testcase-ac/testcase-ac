#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: small for manual verification, but variable
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int group = rnd.next(0, 99);
        int a, b;
        if (group < 10) {
            // both small
            a = rnd.next(1, 20);
            b = rnd.next(1, 20);
        } else if (group < 20) {
            // a small, b large
            a = rnd.next(1, 20);
            b = rnd.next(1001, 50000);
        } else if (group < 30) {
            // a large, b small
            a = rnd.next(1001, 50000);
            b = rnd.next(1, 20);
        } else if (group < 40) {
            // both large
            a = rnd.next(1001, 50000);
            b = rnd.next(1001, 50000);
        } else if (group < 45) {
            // equal values
            a = rnd.next(1, 50000);
            b = a;
        } else if (group < 55) {
            // near triangular boundary: a and b around k*(k+1)/2
            int k = rnd.next(1, 300);
            int s = k * (k + 1) / 2;
            int lo = max(1, s - 10);
            int hi = min(50000, s + 10);
            a = rnd.next(lo, hi);
            b = rnd.next(lo, hi);
        } else {
            // fully random
            a = rnd.next(1, 50000);
            b = rnd.next(1, 50000);
        }
        println(a, b);
    }
    return 0;
}
