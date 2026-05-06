#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the chessboard, must be between 6 and 666 inclusive
    int N = inf.readInt(6, 666, "N");
    inf.readEoln();

    // Read starting position (r, c), both between 1 and N inclusive
    int r = inf.readInt(1, N, "r");
    inf.readSpace();
    int c = inf.readInt(1, N, "c");
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
