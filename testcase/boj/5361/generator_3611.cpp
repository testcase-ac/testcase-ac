#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ++ti) {
        // Four kinds of cases:
        // 0: all zero
        // 1: one non-zero small
        // 2: several small random [0..5]
        // 3: moderate random [0..100]
        int type = rnd.next(0, 3);
        vector<int> c(5, 0);
        if (type == 0) {
            // all zeros
        } else if (type == 1) {
            int j = rnd.next(0, 4);
            c[j] = rnd.next(1, 10);
        } else if (type == 2) {
            for (int i = 0; i < 5; ++i)
                c[i] = rnd.next(0, 5);
        } else {
            for (int i = 0; i < 5; ++i)
                c[i] = rnd.next(0, 100);
        }
        // Print the five counts
        println(c);
    }
    return 0;
}
