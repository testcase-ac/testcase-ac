#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int caseNum = 0;
    while (true) {
        // Set the test case number for better error messages.
        setTestCase(caseNum + 1);

        // Read A and B, allowing 0 for the termination line.
        int A = inf.readInt(0, 1000000000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 1000000000, "B");
        inf.readEoln();

        // Check for termination condition.
        if (A == 0 && B == 0) {
            break;
        }

        // This is a real test case.
        caseNum++;
        ensuref(caseNum <= MAX_CASES,
                "Number of test cases %d exceeds the maximum of %d",
                caseNum, MAX_CASES);

        // Validate constraints for each test case.
        ensuref(1 <= A,
                "In test case %d: A must be at least 1, but got A=%d",
                caseNum, A);
        ensuref(A <= B,
                "In test case %d: A must be <= B, but got A=%d, B=%d",
                caseNum, A, B);
    }

    // After reading the termination line, there must be no extra data.
    inf.readEof();
    return 0;
}
