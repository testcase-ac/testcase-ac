#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int minValue = -536870912;
    const int maxValue = 536870911;
    const int maxCases = 100000;
    // CHECK: The statement has no test-case count limit; cap total set elements
    // to keep primarily numeric inputs below the local practical-size default.
    const int maxTotalElements = 4999999;

    int caseCount = 0;
    int totalElements = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(caseCount <= maxCases, "too many test cases: %d", caseCount);

        totalElements += n;
        ensuref(totalElements <= maxTotalElements,
                "too many set elements in all test cases: %d", totalElements);

        set<int> values;
        for (int i = 0; i < n; ++i) {
            int value = inf.readInt(minValue, maxValue, "s_i");
            inf.readEoln();
            ensuref(values.insert(value).second,
                    "duplicate set element at index %d: %d", i + 1, value);
        }
    }

    inf.readEof();
}
