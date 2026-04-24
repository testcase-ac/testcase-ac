#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read first row: must be a permutation of 1..N
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // Read second row: values in [1..N], duplicates allowed
    vector<int> b = inf.readInts(N, 1, N, "b_i");
    inf.readEoln();

    // Read third row: values in [1..N], duplicates allowed
    vector<int> c = inf.readInts(N, 1, N, "c_i");
    inf.readEoln();

    // Validate that 'a' is indeed a permutation
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = a[i];
        ensuref(!seen[x],
                "Duplicate number %d in first row at position %d", x, i+1);
        seen[x] = 1;
    }
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x],
                "Missing number %d in first row", x);
    }

    inf.readEof();
    return 0;
}
