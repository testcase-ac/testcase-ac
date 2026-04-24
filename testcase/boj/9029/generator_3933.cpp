#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Choose a shape type for diversity:
        // 0: perfect cube
        // 1: one dimension = 1 (slab)
        // 2: two dimensions equal (prism)
        // 3: all dimensions random
        int type = rnd.next(0, 3);
        int W, L, H;

        if (type == 0) {
            // perfect cube
            int d = rnd.next(1, 20);
            W = L = H = d;
        } else if (type == 1) {
            // one dimension is 1
            int idx = rnd.next(0, 2);
            int a = rnd.next(2, 20);
            int b = rnd.next(2, 20);
            if (idx == 0) {
                W = 1; L = a; H = b;
            } else if (idx == 1) {
                W = a; L = 1; H = b;
            } else {
                W = a; L = b; H = 1;
            }
        } else if (type == 2) {
            // two dimensions equal
            int pairIdx = rnd.next(0, 2);
            int d = rnd.next(2, 20);
            int x = rnd.next(1, 20);
            if (pairIdx == 0) {
                W = L = d; H = x;
            } else if (pairIdx == 1) {
                W = H = d; L = x;
            } else {
                L = H = d; W = x;
            }
        } else {
            // fully random
            W = rnd.next(1, 20);
            L = rnd.next(1, 20);
            H = rnd.next(1, 20);
        }

        println(W, L, H);
    }

    return 0;
}
