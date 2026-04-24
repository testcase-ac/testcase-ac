#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the permutation p[1..N]
    vector<int> p = inf.readInts(N, 1, N, "p_i");
    inf.readEoln();

    // Check that p is a valid permutation: no duplicates, all values 1..N present
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = p[i];
        ensuref(!seen[x], "Duplicate value %d found at position %d in the permutation", x, i+1);
        seen[x] = 1;
    }
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x], "Missing value %d in the permutation", x);
    }

    inf.readEof();
    return 0;
}
