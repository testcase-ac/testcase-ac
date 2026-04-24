#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, must be between 1 and 100 inclusive
    inf.readInt(1, 100, "N");
    // Expect exactly one newline after N
    inf.readEoln();
    // No extra data
    inf.readEof();
    return 0;
}
