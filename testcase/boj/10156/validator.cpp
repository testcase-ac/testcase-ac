#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three integers: K, N, M
    int K = inf.readInt(1, 1000, "K");
    inf.readSpace();
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // No further global properties to check beyond the given ranges.
    inf.readEof();
    return 0;
}
