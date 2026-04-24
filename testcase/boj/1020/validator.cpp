#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the counter string: must be 1 to 15 digits, leading zeros allowed.
    // This also ensures N (the length) is between 1 and 15.
    string s = inf.readToken("[0-9]{1,15}", "counter");
    inf.readEoln();    // exactly one newline after the line
    inf.readEof();     // no extra characters after EOF

    return 0;
}
