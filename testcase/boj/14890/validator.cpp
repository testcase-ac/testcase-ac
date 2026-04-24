#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int L = inf.readInt(1, N, "L");
    inf.readEoln();

    // Read the grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Heights are natural numbers ≤ 10
            inf.readInt(1, 10, "height");
            if (j + 1 < N)
                inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
