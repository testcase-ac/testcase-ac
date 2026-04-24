#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 ≤ T ≤ 20)
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    // For each test case, read W, L, H (each 1 ≤ value ≤ 200)
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        int W = inf.readInt(1, 200, "W");
        inf.readSpace();
        int L = inf.readInt(1, 200, "L");
        inf.readSpace();
        int H = inf.readInt(1, 200, "H");
        inf.readEoln();
        
        // No further global constraints to check: any (W,L,H) in range is valid
    }

    // No extra characters after all test cases
    inf.readEof();
    return 0;
}
