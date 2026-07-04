#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    int totalLength = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string s = inf.readToken("[ABC]{1,1000000}", "s");
        inf.readEoln();

        int countA = 0;
        int countB = 0;
        int countC = 0;
        for (char ch : s) {
            if (ch == 'A') {
                ++countA;
            } else if (ch == 'B') {
                ++countB;
            } else {
                ++countC;
            }
        }

        ensuref(countA >= 1, "case %d must contain at least one apple", caseIndex);
        ensuref(countB >= 1, "case %d must contain at least one banana", caseIndex);
        ensuref(countC == 1, "case %d must contain exactly one coconut", caseIndex);

        totalLength += static_cast<int>(s.size());
        ensuref(totalLength <= 1000000, "total string length exceeds 1000000");
    }

    inf.readEof();
}
