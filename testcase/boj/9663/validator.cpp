#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: board size, must be between 1 and 14 inclusive
    int N = inf.readInt(1, 14, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
