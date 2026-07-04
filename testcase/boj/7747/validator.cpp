#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        int length = inf.readInt(1, 100000, "l_i");
        inf.readEoln();

        string pattern = inf.readToken("[abc]{1,100000}", "pattern");
        ensuref(static_cast<int>(pattern.size()) == length,
                "pattern length is %d, expected %d", static_cast<int>(pattern.size()), length);
        inf.readEoln();
    }

    inf.readEof();
}
