#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K: both natural numbers (>=1) and <=1000.
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // No further constraints or global properties to check.
    inf.readEof();
    return 0;
}
