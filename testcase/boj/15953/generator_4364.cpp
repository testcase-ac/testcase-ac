#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // Hyper-parameters for distribution of a
    double ra1 = rnd.next();
    double ra2 = rnd.next();
    double pa0 = min(ra1, ra2);
    double pa1 = max(ra1, ra2); // prize region is [pa0, pa1)
    // Hyper-parameters for distribution of b
    double rb1 = rnd.next();
    double rb2 = rnd.next();
    double pb0 = min(rb1, rb2);
    double pb1 = max(rb1, rb2);

    for (int i = 0; i < T; i++) {
        // Generate a (0..100) with zones: [0]=no entry, [1..21]=prize, [22..100]=no prize
        double ra = rnd.next();
        int a;
        if (ra < pa0) {
            a = 0;
        } else if (ra < pa1) {
            a = rnd.next(1, 21);
        } else {
            a = rnd.next(22, 100);
        }
        // Generate b (0..64) with zones: [0]=no entry, [1..31]=prize, [32..64]=no prize
        double rb = rnd.next();
        int b;
        if (rb < pb0) {
            b = 0;
        } else if (rb < pb1) {
            b = rnd.next(1, 31);
        } else {
            b = rnd.next(32, 64);
        }
        println(a, b);
    }
    return 0;
}
