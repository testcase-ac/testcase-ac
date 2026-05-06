#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 314159, "n");
    inf.readEoln();

    // Output is a single character in {0-9, A-F}, but validator does not check output.

    inf.readEof();
}
