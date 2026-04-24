#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n: number of persons
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // Read the upper-triangle matrix values h_ij for 1 <= i < j <= n
        // For each i = 1..n-1, there are (n - i) integers on the next line
        for (int i = 1; i <= n - 1; i++) {
            int cnt = n - i;
            inf.readInts(cnt, 1, 1000000, "h");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
