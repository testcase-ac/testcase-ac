#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxN = 1000;
    constexpr int kMaxNameLength = 30;
    constexpr int kMaxTotalNames = 100000;

    int totalNames = 0;
    int caseIndex = 0;
    while (true) {
        int n = inf.readInt(0, kMaxN, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ++caseIndex;
        setTestCase(caseIndex);
        ensuref(n >= 2, "n must be at least 2, got %d", n);
        ensuref(n % 2 == 0, "n must be even, got %d", n);

        // CHECK: The statement gives no limit on the number of test cases.
        // Cap the aggregate input at a practical size while preserving the
        // zero-terminated multi-case format.
        totalNames += n;
        ensuref(totalNames <= kMaxTotalNames,
                "total number of names exceeds %d", kMaxTotalNames);

        set<string> names;
        for (int i = 0; i < n; ++i) {
            string name = inf.readToken("[A-Z]{1,30}", "name");
            inf.readEoln();
            ensuref((int)name.size() <= kMaxNameLength,
                    "name length exceeds %d at index %d", kMaxNameLength, i + 1);
            ensuref(names.insert(name).second,
                    "duplicate name in case %d: %s", caseIndex, name.c_str());
        }
    }

    inf.readEof();
}
