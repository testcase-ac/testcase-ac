#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the permutation p_1 ... p_N
    vector<int> p = inf.readInts(N, 1, N, "p_i");
    inf.readEoln();

    // Check that p is a valid permutation of 1..N
    vector<bool> seen(N+1, false);
    for (int i = 0; i < N; i++) {
        int v = p[i];
        ensuref(!seen[v], "Value %d appears more than once in the permutation", v);
        seen[v] = true;
    }
    for (int v = 1; v <= N; v++) {
        ensuref(seen[v], "Value %d from 1..N is missing in the permutation", v);
    }

    inf.readEof();
    return 0;
}
