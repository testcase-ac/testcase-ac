#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int n = rnd.next(1, 10);
    println(n);
    for (int i = 0; i < n; i++) {
        int type = rnd.next(1, 100);
        int a, b;
        if (type <= 10) {
            // equal numbers
            a = rnd.next(1, 1000000);
            b = a;
        } else if (type <= 20) {
            // one is 1
            a = 1;
            b = rnd.next(1, 1000000);
        } else if (type <= 30) {
            // both near the maximum bound
            a = rnd.next(1000000 - 100, 1000000);
            b = rnd.next(1000000 - 100, 1000000);
        } else if (type <= 40) {
            // share a nontrivial gcd (multiple case)
            int d = rnd.next(1, 1000);
            int k1 = rnd.next(1, 1000);
            int k2 = rnd.next(1, 1000);
            a = d * k1;
            b = d * k2;
        } else {
            // general random with skewed distributions
            int t1 = rnd.next(-2, 2);
            int t2 = rnd.next(-2, 2);
            a = rnd.wnext(1000000, t1) + 1;
            b = rnd.wnext(1000000, t2) + 1;
        }
        println(a, b);
    }
    return 0;
}
