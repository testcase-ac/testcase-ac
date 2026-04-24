#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n and validate its bounds.
    int n = inf.readInt(1, 50000, "n");
    // Ensure there's exactly one newline after n.
    inf.readEoln();
    // Ensure no extra data after that.
    inf.readEof();

    return 0;
}
