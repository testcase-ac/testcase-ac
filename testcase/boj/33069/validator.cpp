#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, K
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(N, 300000, "K");
    inf.readEoln();

    // 2. Read M, A, B
    int M = inf.readInt(1, N, "M");
    inf.readSpace();
    int A = inf.readInt(M, N, "A");
    inf.readSpace();
    int B = inf.readInt(M, N, "B");
    inf.readEoln();

    // 3. Read c_1..c_K
    vector<int> c = inf.readInts(K, 1, 1000000000, "c_i");
    inf.readEoln();

    // 4. Read a_1..a_A (Hanbyeol's preferred types)
    vector<int> a = inf.readInts(A, 1, K, "a_i");
    inf.readEoln();

    // 5. Read b_1..b_B (Eunha's preferred types)
    vector<int> b = inf.readInts(B, 1, K, "b_i");
    inf.readEoln();

    // 6. Check that a_i are unique
    {
        set<int> sa(a.begin(), a.end());
        ensuref((int)sa.size() == A, "Hanbyeol's preferred types (a_i) are not unique");
    }

    // 7. Check that b_i are unique
    {
        set<int> sb(b.begin(), b.end());
        ensuref((int)sb.size() == B, "Eunha's preferred types (b_i) are not unique");
    }

    // 8. (Optional) Check that all a_i, b_i are in [1, K] (already checked by readInts)

    // 9. (Optional) For subtask 2, check M=A=B and a=b if needed (not required for global validator)

    // 10. Global property: Is it always possible to satisfy the constraints?
    // That is, is there a selection of N distinct appliance types, with at least M from Hanbyeol's preferred, and at least M from Eunha's preferred?
    // If not, the output should be -1, so the validator should NOT reject such input.
    // Therefore, no need to check for feasibility.

    inf.readEof();
}
