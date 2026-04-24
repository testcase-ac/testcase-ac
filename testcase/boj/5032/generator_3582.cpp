#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for e
    double pe = rnd.next();
    int e;
    if (pe < 0.2) {
        e = 0;
    } else if (pe < 0.5) {
        e = rnd.next(1, 50);
    } else if (pe < 0.8) {
        e = rnd.next(51, 500);
    } else {
        e = rnd.next(501, 999);
    }

    // Hyper-parameter for f
    double pf = rnd.next();
    int f;
    if (pf < 0.2) {
        f = 0;
    } else if (pf < 0.5) {
        f = rnd.next(1, 50);
    } else if (pf < 0.8) {
        f = rnd.next(51, 500);
    } else {
        f = rnd.next(501, 999);
    }

    // Hyper-parameter for c
    double pc = rnd.next();
    int c;
    if (pc < 0.2) {
        c = rnd.next(2, 3);
    } else if (pc < 0.5) {
        c = rnd.next(4, 10);
    } else if (pc < 0.8) {
        c = rnd.next(11, 100);
    } else {
        c = rnd.next(101, 1999);
    }

    // Output one test case: e, f, c
    println(e, f, c);

    return 0;
}
