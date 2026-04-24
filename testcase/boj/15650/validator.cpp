#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M"); // ensures 1 ≤ M ≤ N
    inf.readEoln();

    // No further lines expected
    inf.readEof();
    return 0;
}
