#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of tourists
    // Not specified in statement; assume up to 1e6
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    const int MAXC = 1000000000; // columns and rows are in [0, 10^9 - 1]

    for (int i = 0; i < N; i++) {
        // Read row and column for tourist i (0-based in code, but line number is i+2)
        int R = inf.readInt(0, MAXC - 1, "R_i");
        inf.readSpace();
        int S = inf.readInt(0, MAXC - 1, "S_i");
        inf.readEoln();

        // Field must be free: R & S == 0
        ensuref((R & S) == 0,
                "Blocked field at line %d: (%d, %d)", 
                i + 2, R, S);
    }

    inf.readEof();
    return 0;
}
