#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Read the N patterns
    vector<int> L(N);
    for (int i = 0; i < N; ++i) {
        // Line number of this pattern is i+2 (1-based)
        int line_no = i + 2;
        L[i] = inf.readInt(1, 6, "L_i");
        inf.readSpace();
        // Read a token of 0/1 characters, length 1 to 6
        string pat = inf.readToken("[01]{1,6}", "pattern");
        // Check its length matches L_i
        ensuref((int)pat.size() == L[i],
                "At line %d: length of pattern (%d) != L_i (%d)",
                line_no, (int)pat.size(), L[i]);
        inf.readEoln();
    }

    // Read the M shots
    for (int i = 0; i < M; ++i) {
        // Line number is N+2+i
        long long P = inf.readLong(-100000LL, 100000LL, "P_i");
        inf.readSpace();
        long long D = inf.readLong(-100000LL, 100000LL, "D_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
