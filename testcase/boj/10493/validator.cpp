#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (!inf.eof()) {
        ensuref(testCaseCount < 500, "too many test cases");
        ++testCaseCount;
        setTestCase(testCaseCount);

        for (int line = 0; line < 2; ++line) {
            for (int coefficient = 0; coefficient < 4; ++coefficient) {
                string name = string(line == 0 ? "b_" : "t_") + char('0' + coefficient);
                inf.readDouble(-50000.0, 50000.0, name.c_str());
                if (coefficient + 1 < 4) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    ensuref(testCaseCount >= 1, "input must contain at least one test case");
    inf.readEof();
}
