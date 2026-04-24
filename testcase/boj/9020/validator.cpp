#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 <= T <= 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read an even integer n, 4 <= n <= 10000
    for (int i = 0; i < T; i++) {
        int n = inf.readInt(4, 10000, "n");
        ensuref(n % 2 == 0, "n at test case %d is not even: %d", i+1, n);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
