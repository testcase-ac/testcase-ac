#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    int lineNo = 1;
    while (true) {
        string s = inf.readLine();
        ensuref(!s.empty(), "line %d: each line must contain an arrangement or 0", lineNo);
        ensuref(s.size() <= 10000, "line %d: arrangement has %zu pieces, more than 10000", lineNo, s.size());

        if (s == "0") {
            ensuref(testCases > 0, "input must contain at least one test case before the final 0");
            break;
        }

        for (int i = 0; i < (int)s.size(); ++i) {
            ensuref('1' <= s[i] && s[i] <= '8',
                    "line %d: invalid piece '%c' at position %d", lineNo, s[i], i + 1);
        }

        ++testCases;
        ++lineNo;
    }

    inf.readEof();
}
