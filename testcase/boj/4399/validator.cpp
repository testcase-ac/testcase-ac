#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    int totalLength = 0;

    while (!inf.eof()) {
        setTestCase(caseCount + 1);

        string a = inf.readLine("[a-z]{0,1000}", "a");
        string b = inf.readLine("[a-z]{0,1000}", "b");

        ++caseCount;
        totalLength += static_cast<int>(a.size() + b.size());

        // CHECK: The statement gives an unbounded stream of pairs, so cap both
        // case count and aggregate string length using local unbounded-T policy.
        ensuref(caseCount <= 100000,
                "number of test cases must not exceed 100000, got %d",
                caseCount);
        ensuref(totalLength <= 2000,
                "sum of string lengths must not exceed 2000, got %d",
                totalLength);
    }

    ensuref(caseCount >= 1, "input must contain at least one test case");
    inf.readEof();
}
