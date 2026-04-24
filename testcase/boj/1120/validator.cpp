#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read string A: must be 1 to 50 lowercase letters
    string A = inf.readToken("[a-z]{1,50}", "A");
    inf.readSpace();
    // Read string B: must be 1 to 50 lowercase letters
    string B = inf.readToken("[a-z]{1,50}", "B");
    // End of line after the two tokens
    inf.readEoln();

    // Check that A's length is not greater than B's length
    ensuref((int)A.size() <= (int)B.size(),
            "Length of A (%d) must be <= length of B (%d)", (int)A.size(), (int)B.size());

    // No more input
    inf.readEof();
    return 0;
}
