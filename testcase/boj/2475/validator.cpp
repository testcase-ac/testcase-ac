#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 5 integers, each must be between 0 and 9 inclusive.
    inf.readInts(5, 0, 9, "a_i");
    // After the 5 numbers there must be exactly one end-of-line.
    inf.readEoln();
    // And nothing else in the file.
    inf.readEof();

    return 0;
}
