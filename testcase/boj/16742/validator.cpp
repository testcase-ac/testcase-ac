#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first binary string: only '0' and '1', length between 1 and 4000, no spaces.
    string S = inf.readToken("[01]{1,4000}", "S");
    inf.readEoln();

    // Read second binary string: only '0' and '1', length between 1 and 4000, no spaces.
    string T = inf.readToken("[01]{1,4000}", "T");
    inf.readEoln();

    // No extra content.
    inf.readEof();
    return 0;
}
