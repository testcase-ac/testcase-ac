#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read A: a positive integer without leading zeros, up to 10000 digits
    inf.readToken("[1-9][0-9]{0,9999}", "A");
    // Exactly one space separator
    inf.readSpace();
    // Read B: same constraints as A
    inf.readToken("[1-9][0-9]{0,9999}", "B");
    // End of line after B
    inf.readEoln();
    // No extra content
    inf.readEof();
    return 0;
}
