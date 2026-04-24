#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate current time in seconds [0, 86399]
    int t1 = rnd.next(0, 86399);
    // Choose mode: 0 = equal, 1 = near (± up to 60s), 2 = random
    int mode;
    if (rnd.next(0, 9) == 0) mode = 0;
    else if (rnd.next(0, 1) == 0) mode = 1;
    else mode = 2;
    int t2;
    if (mode == 0) {
        // exactly equal
        t2 = t1;
    } else if (mode == 1) {
        // near time within 60 seconds, forward or backward wrap
        int delta = rnd.next(1, 60);
        if (rnd.next(0, 1) == 0) {
            t2 = (t1 + delta) % 86400;
        } else {
            t2 = (t1 - delta + 86400) % 86400;
        }
    } else {
        // fully random time
        t2 = rnd.next(0, 86399);
    }
    // Convert to hh:mm:ss
    int h1 = t1 / 3600, m1 = (t1 % 3600) / 60, s1 = t1 % 60;
    int h2 = t2 / 3600, m2 = (t2 % 3600) / 60, s2 = t2 % 60;
    // Output
    printf("%02d:%02d:%02d\n", h1, m1, s1);
    printf("%02d:%02d:%02d\n", h2, m2, s2);
    return 0;
}
