#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the octal number as a token consisting only of digits 0-7.
    // The length must be between 1 and 333,334 inclusive.
    string oct = inf.readToken("[0-7]+", "octal");
    ensuref(oct.size() >= 1 && oct.size() <= 333334,
            "Length of octal number must be between 1 and 333,334, but got %zu", oct.size());

    // The line must end here.
    inf.readEoln();

    // No extra content.
    inf.readEof();
    return 0;
}
