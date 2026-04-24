#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXV = 1000000;
    const int MAX_CASES = 100000;

    int real_cases = 0;
    while (true) {
        // Read two integers and the end of line
        int a = inf.readInt(0, MAXV, "a");
        inf.readSpace();
        int b = inf.readInt(0, MAXV, "b");
        inf.readEoln();

        // Check for the terminating line
        if (a == 0 && b == 0) {
            break;
        }

        // For real cases, enforce positivity
        ensuref(a >= 1, "First integer must be >=1 for a real test case, got %d", a);
        ensuref(b >= 1, "Second integer must be >=1 for a real test case, got %d", b);

        real_cases++;
        ensuref(real_cases <= MAX_CASES,
                "Number of test cases exceeds %d: got %d",
                MAX_CASES, real_cases);
    }

    // After the sentinel line, there must be nothing else
    inf.readEof();
    return 0;
}
