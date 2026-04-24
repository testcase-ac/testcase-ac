#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of missions and number of Jimmy Bonds
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read the N x N matrix of probabilities (integers in [0,100])
    char buf[32];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Name each entry for clearer error messages
            sprintf(buf, "p_%d_%d", i+1, j+1);
            inf.readInt(0, 100, buf);
            if (j < N-1) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
