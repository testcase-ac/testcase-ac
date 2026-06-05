#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000; // CHECK: statement gives no upper bound on the number of sets.
    const int MAX_TOTAL_NAME_CHARS = 10000000; // CHECK: practical cap for unbounded string input size.

    int cases = 0;
    int totalNameChars = 0;

    while (true) {
        int n = inf.readInt(0, 15, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++cases;
        ensuref(cases <= MAX_CASES, "too many sets: %d", cases);
        setTestCase(cases);

        int previousLength = 0;
        for (int i = 1; i <= n; ++i) {
            string name = inf.readToken("[^]{1,25}", "name");
            inf.readEoln();

            ensuref((int)name.size() >= previousLength,
                    "name %d has length %d after previous length %d",
                    i, (int)name.size(), previousLength);
            previousLength = (int)name.size();

            totalNameChars += (int)name.size();
            ensuref(totalNameChars <= MAX_TOTAL_NAME_CHARS,
                    "total name characters exceed %d",
                    MAX_TOTAL_NAME_CHARS);
        }
    }

    ensuref(cases >= 1, "input must contain at least one set");
    inf.readEof();
}
