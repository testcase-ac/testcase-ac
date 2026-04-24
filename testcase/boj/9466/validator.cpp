#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Number of students
        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();
        // Each student selects exactly one student in range [1, n]
        inf.readInts(n, 1, n, "selection");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
