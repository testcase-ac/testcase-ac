#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the stack order: should be a permutation of 1..N
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, N, "plate");
        inf.readEoln();
        ensuref(!seen[x],
                "Duplicate plate label %d at line %d", x, i+2);
        seen[x] = 1;
    }

    // Ensure all input is consumed
    inf.readEof();
    return 0;
}
