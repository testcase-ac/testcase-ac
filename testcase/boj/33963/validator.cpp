#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N < 10^9
    inf.readInt(1, 1000000000 - 1, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
