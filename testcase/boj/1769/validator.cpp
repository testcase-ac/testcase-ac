#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the big number X: it must not start with '0' and consist only of digits
    string X = inf.readToken("[1-9][0-9]*", "X");
    // Check the length constraint: at most 1,000,000 digits
    ensuref((int)X.length() <= 1000000,
            "length of X must be at most 1000000, but got %d", (int)X.length());

    // No extra tokens on the line
    inf.readEoln();
    // End of file immediately after
    inf.readEof();

    return 0;
}
