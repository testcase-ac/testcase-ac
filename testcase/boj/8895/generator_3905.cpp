#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Choose a scenario to diversify cases
        int type = rnd.next(0, 3);
        int n, l, r;
        if (type == 0) {
            // Small n, random l and r
            n = rnd.next(1, 5);
            l = rnd.next(1, n);
            r = rnd.next(1, n);
        } else if (type == 1) {
            // Large n, random l and r
            n = rnd.next(16, 20);
            l = rnd.next(1, n);
            r = rnd.next(1, n);
        } else if (type == 2) {
            // Edge: one side sees exactly 1
            n = rnd.next(2, 20);
            if (rnd.next(0, 1) == 0) {
                l = 1;
                r = rnd.next(1, n);
            } else {
                r = 1;
                l = rnd.next(1, n);
            }
        } else {
            // Edge: one or both sides see all sticks
            n = rnd.next(2, 20);
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                // both l and r equals n
                l = n;
                r = n;
            } else if (sub == 1) {
                l = n;
                r = rnd.next(1, n);
            } else {
                r = n;
                l = rnd.next(1, n);
            }
        }
        println(n, l, r);
    }

    return 0;
}
