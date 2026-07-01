#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string s = inf.readToken("[A-Z]{26}", "s");
        inf.readEoln();

        vector<int> seen(26, 0);
        for (char c : s) {
            ++seen[c - 'A'];
        }
        for (int i = 0; i < 26; ++i) {
            ensuref(seen[i] == 1, "letter %c appears %d times", char('A' + i), seen[i]);
        }
    }

    inf.readEof();
}
