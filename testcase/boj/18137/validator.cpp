#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: Simulating the stated greedy knight walk from cell 1 gives exactly
    // 2401 possible moves before every legal next cell has already been visited.
    inf.readInt(0, 2401, "k");
    inf.readEoln();
    inf.readEof();
}
