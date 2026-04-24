#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read temperature array
    inf.readInts(N, -100, 100, "temp");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
