#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N and validate its range.
    int N = inf.readInt(1, 100000, "N");
    // After N, there must be exactly one end of line.
    inf.readEoln();

    // No more data allowed.
    inf.readEof();

    return 0;
}
