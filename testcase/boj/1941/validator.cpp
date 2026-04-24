#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input must consist of exactly 5 lines, each with exactly 5 characters 'S' or 'Y'.
    for (int i = 1; i <= 5; i++) {
        // Read a line of exactly 5 characters, each either 'S' or 'Y'
        inf.readLine("[SY]{5}", string("row_") + to_string(i));
    }
    // After the 5th line (which consumes its EOLN), there must be no more input
    inf.readEof();

    return 0;
}
