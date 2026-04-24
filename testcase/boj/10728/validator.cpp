#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, one integer N
    for (int tc = 0; tc < T; tc++) {
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
