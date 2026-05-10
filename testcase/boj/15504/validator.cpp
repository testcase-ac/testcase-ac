#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 300, "N");
    inf.readEoln();

    // Read A_i and ensure they are distinct
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();
    {
        set<int> seenA;
        for (int i = 0; i < N; i++) {
            ensuref(!seenA.count(A[i]),
                    "Duplicate A_i detected at index %d: %d",
                    i+1, A[i]);
            seenA.insert(A[i]);
        }
    }

    // Read H_i
    vector<int> H = inf.readInts(N, 1, 1000000, "H_i");
    inf.readEoln();

    // Read L_i, each between 2 and N-1
    // Note: for N=2 this range is invalid, but inputs must satisfy constraints.
    vector<int> L = inf.readInts(N, 2, N-1, "L_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
