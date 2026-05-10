#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 0, 100000, "A_i");
    inf.readEoln();

    // 3. Read p, q, r, S
    int p = inf.readInt(1, 4999, "p");
    inf.readSpace();
    int q = inf.readInt(1, 4999, "q");
    inf.readSpace();
    int r = inf.readInt(p+q, 9999, "r");
    inf.readSpace();
    long long S = inf.readLong(1LL, 20000000000LL, "S");
    inf.readEoln();

    // 4. No further constraints to check (all are per-value and already checked)
    // 5. Check file ends correctly
    inf.readEof();
}
