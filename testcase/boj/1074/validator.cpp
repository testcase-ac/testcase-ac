#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and validate range
    int N = inf.readInt(1, 15, "N");
    inf.readSpace();

    // Compute maximum valid r and c: [0, 2^N - 1]
    int limit = (1 << N) - 1;
    int r = inf.readInt(0, limit, "r");
    inf.readSpace();
    int c = inf.readInt(0, limit, "c");

    // End of line and end of file
    inf.readEoln();
    inf.readEof();

    return 0;
}
