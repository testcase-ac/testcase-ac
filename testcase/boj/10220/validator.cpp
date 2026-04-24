#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: single integer N (1 ≤ N ≤ 100)
    for (int tc = 0; tc < T; tc++) {
        inf.readInt(1, 100, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
