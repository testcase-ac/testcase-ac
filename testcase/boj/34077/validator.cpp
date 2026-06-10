#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 100000, "sum of N exceeds 100000 at case %d", caseIndex);

        string expression = inf.readLine("[^]{3,200001}", "expression");
        ensuref((int)expression.size() == 2 * n + 1,
                "case %d expression length is %d, expected %d",
                caseIndex,
                (int)expression.size(),
                2 * n + 1);

        for (int i = 0; i < (int)expression.size(); ++i) {
            if (i % 2 == 0) {
                ensuref('0' <= expression[i] && expression[i] <= '9',
                        "case %d expression character %d must be a digit",
                        caseIndex,
                        i + 1);
            } else {
                ensuref(expression[i] == '+' || expression[i] == '-',
                        "case %d expression character %d must be '+' or '-'",
                        caseIndex,
                        i + 1);
            }
        }
    }

    inf.readEof();
}
