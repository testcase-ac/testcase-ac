#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the temperature sequence
    inf.readInts(N, -100, 100, "temperature");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
