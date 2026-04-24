#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of applicants in this test case
        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        // To ensure each rank list is a permutation of [1..N]
        vector<char> seenDoc(N+1, 0), seenInt(N+1, 0);

        for (int i = 1; i <= N; ++i) {
            // Read document rank and interview rank
            int doc = inf.readInt(1, N, "doc_rank");
            inf.readSpace();
            int iv  = inf.readInt(1, N, "interv_rank");
            inf.readEoln();

            // Check for duplicates in each ranking
            ensuref(!seenDoc[doc],
                    "Duplicate document rank %d in test case %d at line %d", 
                    doc, tc, i);
            seenDoc[doc] = 1;

            ensuref(!seenInt[iv],
                    "Duplicate interview rank %d in test case %d at line %d",
                    iv, tc, i);
            seenInt[iv] = 1;
        }
    }

    inf.readEof();
    return 0;
}
