#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read positions
    vector<bool> seen(N+1, false);
    for (int i = 0; i < M; i++) {
        if (i > 0)
            inf.readSpace();
        int x = inf.readInt(1, N, "pos");
        ensuref(!seen[x], "Duplicate position %d at index %d", x, i+1);
        seen[x] = true;
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
