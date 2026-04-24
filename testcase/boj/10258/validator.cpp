#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: not specified, assume 1 to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a bitstring B of length 2 to 31
    for (int tc = 0; tc < T; tc++) {
        // readLine consumes exactly one EOLN, and matches entire line
        inf.readLine("[01]{2,31}", "B");
    }

    inf.readEof();
    return 0;
}
