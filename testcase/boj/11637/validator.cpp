#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 < T < 500
    int T = inf.readInt(2, 499, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // For each test case:
        // n: number of candidates, 2 <= n <= 10
        int n = inf.readInt(2, 10, "n");
        inf.readEoln();

        // Next n lines: votes for each candidate, 1 <= votes <= 50000
        for (int i = 0; i < n; i++) {
            int votes = inf.readInt(1, 50000, "votes_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
