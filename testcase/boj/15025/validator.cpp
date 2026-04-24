#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the two tine counts ℓ and r, each between 0 and 20 inclusive.
    int l = inf.readInt(0, 20, "l");
    inf.readSpace();  // exactly one whitespace between the two integers
    int r = inf.readInt(0, 20, "r");
    inf.readEoln();   // end of the single input line

    // No further content allowed.
    inf.readEof();
    return 0;
}
