#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (true) {
        string reading = inf.readLine("[0-9]{1,9}", "reading");
        if (reading == "0") {
            break;
        }

        ++testCaseCount;
        setTestCase(testCaseCount);
        ensuref(2 <= (int)reading.size() && (int)reading.size() <= 9,
                "reading length must be between 2 and 9, got %d",
                (int)reading.size());

        // CHECK: the statement does not bound the number of test cases.
        ensuref(testCaseCount <= 100000, "too many test cases: %d", testCaseCount);
    }

    inf.readEof();
}
