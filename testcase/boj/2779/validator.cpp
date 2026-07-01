#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readToken("[a-z]{1,50}", "sentence");
        inf.readEoln();

        int n = inf.readInt(1, 50, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            // CHECK: The statement omits a bound for each secret word length;
            // cap it at the target sentence maximum because longer words cannot
            // be used in a valid segmentation of a sentence of length at most 50.
            inf.readToken("[a-z]{1,50}", "word");
            inf.readEoln();
        }
    }

    inf.readEof();
}
