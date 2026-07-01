#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    int totalNames = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);

        ensuref(n >= 2, "n must be at least 2, found %d", n);
        ensuref(n % 2 == 0, "n must be even, found %d", n);

        totalNames += n;
        // CHECK: the statement gives no number-of-cases limit; cap aggregate names for practical validation.
        ensuref(totalNames <= 100000, "sum of n across test cases exceeds 100000");

        set<string> names;
        for (int i = 0; i < n; ++i) {
            string name = inf.readToken("[A-Z]{1,30}", "name");
            inf.readEoln();
            ensuref(names.insert(name).second, "duplicate name in case %d: %s", caseCount, name.c_str());
        }
    }

    inf.readEof();
}
