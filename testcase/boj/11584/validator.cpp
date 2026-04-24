#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T (1 ≤ T ≤ 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read numerator a and denominator b
    for (int tc = 0; tc < T; tc++) {
        int a = inf.readInt(0, 100000, "a");   // 0 ≤ a ≤ 100000
        inf.readSpace();
        int b = inf.readInt(1, 100000, "b");   // 1 ≤ b ≤ 100000
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
