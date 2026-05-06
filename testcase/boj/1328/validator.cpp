#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of buildings N
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    // Read number visible from left L
    int L = inf.readInt(1, N, "L");
    inf.readSpace();
    // Read number visible from right R
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // No other global properties are enforced by the statement;
    // zero-answer cases (e.g., L+R > N+1) are allowed.

    inf.readEof();
    return 0;
}
