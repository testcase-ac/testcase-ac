#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K with their constraints
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int K = inf.readInt(1, 200, "K");
    inf.readEoln();

    // No further structural constraints on the input
    inf.readEof();
    return 0;
}
