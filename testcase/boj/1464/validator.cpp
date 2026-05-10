#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line containing S
    string S = inf.readLine("[A-Z]{1,50}", "S");
    // The regex ensures:
    // - length between 1 and 50 (inclusive)
    // - only uppercase A-Z characters

    // No further structure, no multiple test cases.

    inf.readEof();
}
