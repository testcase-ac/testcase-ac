#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of characters, must be between 1 and 9 inclusive
    int n = inf.readInt(1, 9, "n");
    inf.readEoln();

    // Read the concatenated binary string of length exactly 6 * n
    string bits = inf.readToken("[01]+", "bits");
    ensuref((int)bits.size() == 6 * n,
            "The length of the binary string must be 6 * n = %d, but got %d",
            6 * n, (int)bits.size());
    inf.readEoln();

    inf.readEof();
    return 0;
}
