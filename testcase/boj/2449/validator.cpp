#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    // Read the colors of the bulbs
    inf.readInts(N, 1, K, "color");
    inf.readEoln();

    inf.readEof();
    return 0;
}
