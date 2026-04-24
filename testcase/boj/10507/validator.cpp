#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test has exactly 3 lines: each a non-empty string of [a-z?], length <= 1e6
    const int MAXL = 1000000;
    for (int tc = 0; tc < T; tc++) {
        // Word 1
        string w1 = inf.readToken("[a-z?]+", "w1");
        ensuref(w1.size() <= MAXL,
                "Length of w1 in test case %d is %d, but must be <= %d",
                tc+1, (int)w1.size(), MAXL);
        inf.readEoln();

        // Word 2
        string w2 = inf.readToken("[a-z?]+", "w2");
        ensuref(w2.size() <= MAXL,
                "Length of w2 in test case %d is %d, but must be <= %d",
                tc+1, (int)w2.size(), MAXL);
        inf.readEoln();

        // Word 3
        string w3 = inf.readToken("[a-z?]+", "w3");
        ensuref(w3.size() <= MAXL,
                "Length of w3 in test case %d is %d, but must be <= %d",
                tc+1, (int)w3.size(), MAXL);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
