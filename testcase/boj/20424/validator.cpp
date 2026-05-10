#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the nickname S
    string S = inf.readToken("[A-Za-z0-9]{1,1000000}", "S");
    inf.readEoln();

    // Check for leading zeros in numbers? Not relevant; S is arbitrary string of letters/digits.

    // No other constraints in the statement.
    // |S| <= 1,000,000, already checked by regex.

    inf.readEof();
}
