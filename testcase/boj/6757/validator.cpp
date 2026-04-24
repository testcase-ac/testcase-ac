#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer X, ensure it's within [2, 1e9].
    int X = inf.readInt(2, 1000000000, "X");
    inf.readEoln();

    // No further structural constraints on X.
    // The solution will handle checking bases and palindromes.

    inf.readEof();
    return 0;
}
