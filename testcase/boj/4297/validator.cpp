#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 499999;
    const int maxValue = 999999999;
    // CHECK: The statement does not bound the number of test cases; cap total
    // sequence values to keep primarily numeric inputs below local size limits.
    const int maxTotalValues = 4999999;

    int totalValues = 0;
    for (int caseIndex = 1;; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(0, maxN, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ensuref(totalValues <= maxTotalValues - n,
                "too many sequence values: previous total %d, next n %d",
                totalValues, n);
        totalValues += n;

        unordered_set<int> seen;
        seen.reserve(static_cast<size_t>(n) * 2);
        for (int i = 0; i < n; ++i) {
            int value = inf.readInt(0, maxValue, "a_i");
            inf.readEoln();
            ensuref(seen.insert(value).second,
                    "duplicate value at case %d, index %d: %d",
                    caseIndex, i + 1, value);
        }
    }

    inf.readEof();
}
