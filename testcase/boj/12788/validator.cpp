#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of CTP members
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read number of teams M and team size K
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Read the pens each member has
    vector<int> A = inf.readInts(N, 0, 100, "A_i");
    inf.readEoln();

    // Ensure all pen counts are distinct
    set<int> seen;
    for (int i = 0; i < N; i++) {
        ensuref(!seen.count(A[i]),
                "Duplicate pen count detected for member %d: %d",
                i+1, A[i]);
        seen.insert(A[i]);
    }

    // No extra input
    inf.readEof();
    return 0;
}
