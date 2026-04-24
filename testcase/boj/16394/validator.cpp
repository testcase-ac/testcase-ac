#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the year N and validate its range [1946, 1e6]
    int N = inf.readInt(1946, 1000000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
