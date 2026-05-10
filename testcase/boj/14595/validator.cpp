#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(0, 5000, "M");
    inf.readEoln();

    // For each action, read x, y
    for (int i = 0; i < M; ++i) {
        int x = inf.readInt(1, N-1, "x");
        inf.readSpace();
        int y = inf.readInt(x+1, N, "y");
        inf.readEoln();
    }

    inf.readEof();
}
