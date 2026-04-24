#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N
    int N = inf.readInt(3, 1000, "N");
    inf.readEoln();

    // Each of the next N lines: three distinct integers in {1,2,3}, one of each
    for (int i = 1; i <= N; ++i) {
        int s1 = inf.readInt(1, 3, "score1");
        inf.readSpace();
        int s2 = inf.readInt(1, 3, "score2");
        inf.readSpace();
        int s3 = inf.readInt(1, 3, "score3");
        inf.readEoln();

        // Must be a permutation of {1,2,3}
        ensuref(s1 != s2 && s1 != s3 && s2 != s3,
                "Line %d: scores must be distinct, got (%d, %d, %d)", i, s1, s2, s3);
        ensuref(s1 + s2 + s3 == 6,
                "Line %d: scores must be exactly 1,2,3 (sum=6), got sum %d", i, s1 + s2 + s3);
    }

    // No extra data
    inf.readEof();
    return 0;
}
