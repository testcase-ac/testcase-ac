#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the length of the roll cake
    int L = inf.readInt(1, 1000, "L");
    inf.readEoln();

    // Read the number of audience members
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // For each audience member, read P_i and K_i
    for (int i = 1; i <= N; i++) {
        int P = inf.readInt(1, L,   format("P_%d", i).c_str());
        inf.readSpace();
        int K = inf.readInt(1, L,   format("K_%d", i).c_str());
        inf.readEoln();
        ensuref(P <= K,
                "Invalid range at line %d: P_%d = %d > K_%d = %d",
                i + 2, i, P, i, K);
    }

    inf.readEof();
    return 0;
}
