#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalTextLength = 0;
    int testCaseCount = 0;

    while (true) {
        int m = inf.readInt(0, 128, "m");
        inf.readEoln();

        if (m == 0) {
            break;
        }

        ensuref(m >= 1, "m must be 0 only for the terminating line");
        setTestCase(++testCaseCount);

        string text = inf.readLine("[^]{1,1000000}", "text");
        for (int i = 0; i < static_cast<int>(text.size()); ++i) {
            unsigned char ch = static_cast<unsigned char>(text[i]);
            ensuref(32 <= ch && ch <= 126, "text contains non-printable ASCII at position %d", i + 1);
        }
        totalTextLength += static_cast<long long>(text.size());

        // CHECK: The statement bounds each text line but not the number of cases;
        // cap aggregate text size to keep repository test inputs practical.
        ensuref(totalTextLength <= 10000000LL, "total text length exceeds 10000000");
    }

    ensuref(testCaseCount >= 1, "at least one non-terminating test case is required");
    inf.readEof();
}
