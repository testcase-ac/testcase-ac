#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[+-]{1,200000}", "s");
    inf.readEoln();
    inf.readEof();

    int n = (int)s.size();
    vector<char> expectNumber(n + 1, false), endNumber(n + 1, false);
    expectNumber[0] = true;

    for (int i = 0; i <= n; ++i) {
        if (expectNumber[i]) {
            if (i < n) {
                endNumber[i + 1] = true;
            }
            if (i + 1 < n && s[i] == '+' && s[i + 1] == '-') {
                endNumber[i + 2] = true;
            }
        }
        if (endNumber[i] && i < n) {
            expectNumber[i + 1] = true;
        }
    }

    ensuref(endNumber[n], "s has no valid interpretation");
}
