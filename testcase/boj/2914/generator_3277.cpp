#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 2);
    int A, I;
    if (mode == 0) {
        // Single song edge case
        A = 1;
        int t = rnd.next(-1, 2);
        I = rnd.wnext(100, t) + 1;
    } else if (mode == 1) {
        // Minimum average edge case
        I = 1;
        int t = rnd.next(-1, 2);
        A = rnd.wnext(100, t) + 1;
    } else {
        // General case with weighted bias
        int t1 = rnd.next(-2, 2);
        A = rnd.wnext(100, t1) + 1;
        int t2 = rnd.next(-2, 2);
        I = rnd.wnext(100, t2) + 1;
    }
    println(A, I);
    return 0;
}
