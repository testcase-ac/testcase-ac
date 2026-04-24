#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read adjacency matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Name each element for clear error reporting
            char name[32];
            sprintf(name, "a[%d][%d]", i+1, j+1);
            int x = inf.readInt(0, 1, name);
            // No self-loops allowed: diagonal must be zero
            if (i == j) {
                ensuref(x == 0,
                        "Diagonal element %s must be 0 but found %d", 
                        name, x);
            }
            if (j + 1 < N) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
