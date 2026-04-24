#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string: must consist only of '0' and '1', length between 1 and 150.
    inf.readToken("[01]{1,150}", "s");

    // Ensure exactly one newline after the string, then EOF.
    inf.readEoln();
    inf.readEof();

    return 0;
}
