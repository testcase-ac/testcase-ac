#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S as one token (no whitespace inside)
    string S = inf.readToken("[^]+", "S");
    // Check length constraints
    ensuref((int)S.size() >= 1 && (int)S.size() <= 100000,
            "Length of S must be between 1 and 100000, found %d", (int)S.size());
    // After the string, there must be exactly one end-of-line
    inf.readEoln();
    // And then immediately EOF
    inf.readEof();

    return 0;
}
