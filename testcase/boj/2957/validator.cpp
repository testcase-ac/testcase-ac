#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read sequence and check distinctness
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, N, "A_i");
        inf.readEoln();
        ensuref(!seen[x], "Duplicate value at index %d: %d", i+1, x);
        seen[x] = 1;
    }

    inf.readEof();
    return 0;
}
