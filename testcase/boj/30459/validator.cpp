#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, R
    int N = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 40000, "M");
    inf.readSpace();
    long long R = inf.readLong(1LL, 1000000000LL, "R");
    inf.readEoln();

    // Second line: N distinct stake positions A_i
    vector<int> A = inf.readInts(N, -20000, 20000, "A_i");
    inf.readEoln();
    {
        // Check distinctness of A
        set<int> seenA;
        for (int i = 0; i < N; i++) {
            int x = A[i];
            ensuref(!seenA.count(x),
                    "Duplicate stake position at index %d: %d", i, x);
            seenA.insert(x);
        }
    }

    // Third line: M distinct pole lengths B_i
    vector<int> B = inf.readInts(M, 1, 40000, "B_i");
    inf.readEoln();
    {
        // Check distinctness of B
        set<int> seenB;
        for (int i = 0; i < M; i++) {
            int x = B[i];
            ensuref(!seenB.count(x),
                    "Duplicate pole length at index %d: %d", i, x);
            seenB.insert(x);
        }
    }

    // End of file
    inf.readEof();
    return 0;
}
