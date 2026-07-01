#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalLength = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string s = inf.readToken("[A-Z]{1,100}", "S");
        inf.readEoln();

        string visible = inf.readToken("[A-Z*]{1,100}", "visible");
        inf.readEoln();

        string hidden = inf.readToken("[A-Z*]{1,100}", "hidden");
        inf.readEoln();

        ensuref(visible.size() == hidden.size(),
                "visible and hidden strings have different lengths: %d and %d",
                int(visible.size()), int(hidden.size()));

        for (int i = 0; i < int(visible.size()); ++i) {
            ensuref((visible[i] == '*') == (hidden[i] == '*'),
                    "joker mismatch at card %d: visible=%c hidden=%c",
                    i + 1, visible[i], hidden[i]);
        }

        totalLength += int(s.size()) + int(visible.size()) + int(hidden.size());
        // CHECK: The statement gives no upper bound for the number of test cases.
        ensuref(totalLength <= 100000,
                "total input string length exceeds practical cap: %d",
                totalLength);
    }

    inf.readEof();
}
