#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        set<string> dictWords; // To check for duplicate dictionary words

        // N: number of dictionary words
        int N = inf.readInt(1, 50000, "N");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            string DW = inf.readToken("[a-z]{1,40}", "DW");
            inf.readEoln();

            ensuref(dictWords.insert(DW).second, 
                "Duplicate dictionary word at test case %d, index %d: '%s'", tc, i+1, DW.c_str());
        }

        // Q: number of queries
        int Q = inf.readInt(1, 50000, "Q");
        inf.readEoln();

        set<string> queryWords; // To check for duplicate query words within this test case

        for (int i = 0; i < Q; ++i) {
            string QW = inf.readToken("[a-z]{1,40}", "QW");
            inf.readEoln();

            ensuref(queryWords.insert(QW).second,
                "Duplicate query word at test case %d, query %d: '%s'", tc, i+1, QW.c_str());
        }
    }

    inf.readEof();
}
