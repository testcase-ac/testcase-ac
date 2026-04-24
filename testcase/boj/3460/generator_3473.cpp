#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Hyper-parameters for diverse n values
        int type = rnd.next(0, 4);
        int n;
        if (type == 0) {
            // small random
            n = rnd.next(1, 100);
        } else if (type == 1) {
            // large random
            n = rnd.next(100000, 1000000);
        } else if (type == 2) {
            // single bit set
            int e = rnd.next(0, 19);
            n = 1 << e;
        } else if (type == 3) {
            // mask of consecutive ones
            int b = rnd.next(1, 19);
            n = (1 << b) - 1;
        } else {
            // exactly two bits set
            int e1 = rnd.next(0, 19);
            int e2;
            do {
                e2 = rnd.next(0, 19);
            } while (e2 == e1);
            n = (1 << e1) | (1 << e2);
        }
        println(n);
    }

    return 0;
}
