#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the permutation of size N
    vector<bool> seen(N+1, false);
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, "a_i");
        inf.readEoln();
        ensuref(!seen[x],
                "Duplicate value %d found at position %d", x, i);
        seen[x] = true;
    }

    // After reading all N lines, we must have consumed the entire file
    inf.readEof();
    return 0;
}
