#include "testlib.h"

#include <string>

using namespace std;

bool isChromosomeString(const string& s) {
    for (char c : s) {
        if (c != 'p' && c != 'i' && c != 'n' && c != 'k' &&
            c != 'h' && c != 'a' && c != 'r' && c != 'e') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 8, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int q = inf.readInt(2, 15000, "Q");
        inf.readEoln();

        for (int i = 1; i <= q; ++i) {
            string s = inf.readToken("[a-z]+", "command");
            inf.readEoln();

            ensuref(s.size() == 10 || s.size() == 44,
                    "command %d has length %d, expected 10 or 44",
                    i, (int)s.size());
            ensuref(isChromosomeString(s),
                    "command %d contains a character outside pinkhare", i);
        }
    }

    inf.readEof();
}
