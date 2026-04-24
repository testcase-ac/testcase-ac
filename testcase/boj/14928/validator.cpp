#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the big integer N: must be a non-empty string of digits, up to 1,000,000 digits.
    inf.readToken("[0-9]{1,1000000}", "N");
    inf.readEoln();

    // No more input allowed.
    inf.readEof();
    return 0;
}
