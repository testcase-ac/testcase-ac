#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 4, "N");
    inf.readEoln();

    // Read A_{i,j}
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            inf.readInt(0, 1000, "A_{i,j}");
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
