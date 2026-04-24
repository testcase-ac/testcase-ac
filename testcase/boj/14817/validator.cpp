#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 ≤ T ≤ 100
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, C, M
        // 2 ≤ N ≤ 1000
        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        // 1 ≤ C ≤ 1000  (number of customers)
        int C = inf.readInt(1, 1000, "C");
        inf.readSpace();
        // 1 ≤ M ≤ 1000
        int M = inf.readInt(1, 1000, "M");
        inf.readEoln();

        // Read M tickets: position P_i and buyer B_i
        for (int i = 1; i <= M; i++) {
            int P = inf.readInt(1, N, "P_i");
            inf.readSpace();
            int B = inf.readInt(1, C, "B_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
