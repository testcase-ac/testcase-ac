#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: the length of the move sequence, 1 <= n < 50
    int n = inf.readInt(1, 49, "n");
    inf.readEoln();

    // Read the move sequence
    // It must consist only of characters 'F', 'L', 'R'
    string s = inf.readToken("[FLR]+", "s");
    // Check exact length
    ensuref((int)s.size() == n,
            "The length of the move string (%%d) does not match n (%%d)", 
            (int)s.size(), n);
    inf.readEoln();

    // No further input
    inf.readEof();

    return 0;
}
