#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N and k
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, N, "k");
    inf.readEoln();

    // Read and validate scores
    inf.readInts(N, 0, 10000, "x");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
