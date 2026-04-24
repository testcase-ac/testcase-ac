#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the board length n: single integer between 3 and 2000
    int n = inf.readInt(3, 2000, "n");
    // Ensure exactly one newline after n
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
