#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int columns = inf.readInt(0, 20, "columns");
        inf.readEoln();

        if (columns == 0) {
            break;
        }

        ensuref(columns >= 2, "columns must be either 0 or in [2, 20], got %d", columns);
        ++caseCount;
        // CHECK: the statement gives no input-set count bound, so use the local default cap.
        ensuref(caseCount <= 100000, "too many input sets: %d", caseCount);
        setTestCase(caseCount);

        string encrypted = inf.readToken("[a-z]{1,200}", "encrypted");
        inf.readEoln();
        ensuref(static_cast<int>(encrypted.size()) % columns == 0,
                "encrypted length %d is not divisible by columns %d",
                static_cast<int>(encrypted.size()),
                columns);
    }

    inf.readEof();
}
