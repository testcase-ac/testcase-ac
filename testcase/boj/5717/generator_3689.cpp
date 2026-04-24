#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases (excluding the terminating 0 0)
    int tmode = rnd.next(-1, 1);
    int T = rnd.wnext(10, tmode) + 1;  // yields 1 to 10

    // Generate T test cases
    for (int i = 0; i < T; i++) {
        // Hyper-parameters for distributions of M and F
        int mmode = rnd.next(-2, 2);
        int fmode = rnd.next(-2, 2);
        int M = rnd.wnext(5, mmode) + 1;  // yields 1 to 5
        int F = rnd.wnext(5, fmode) + 1;  // yields 1 to 5
        println(M, F);
    }

    // Termination line
    println(0, 0);

    return 0;
}
