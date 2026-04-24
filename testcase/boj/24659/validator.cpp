#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read permutation P of size N
    vector<int> P = inf.readInts(N, 1, N, "P_i");
    inf.readEoln();

    // Ensure P is a valid permutation: all values 1..N exactly once
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = P[i];
        ensuref(!seen[x], "Duplicate value in P at index %d: %d", i+1, x);
        seen[x] = 1;
    }

    // Read A array
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    // Read B array
    vector<long long> B = inf.readLongs(N, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    // No further global constraints to check for input validity
    inf.readEof();
    return 0;
}
