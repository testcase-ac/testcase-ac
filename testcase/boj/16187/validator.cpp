#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 5000, "T");
    inf.readEoln();

    // Each test case: one integer N
    for (int i = 0; i < T; i++) {
        int N = inf.readInt(3, 5000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
