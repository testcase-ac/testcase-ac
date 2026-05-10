#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of poles N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the permutation: N natural numbers each in [1, N]
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // Check that it's a bijection: no duplicate right-pole connections
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = a[i];
        ensuref(!seen[x],
                "Duplicate connection to right pole %d at position %d", 
                x, i+1);
        seen[x] = 1;
    }

    inf.readEof();
    return 0;
}
