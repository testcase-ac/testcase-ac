#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of direction rotations (1 ≤ N ≤ 22)
    inf.readInt(1, 22, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
