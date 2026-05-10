#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read the grid of heights
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Each height must be between 1 and 100
            inf.readInt(1, 100, format("H[%d][%d]", i+1, j+1).c_str());
            if (j + 1 < M)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
