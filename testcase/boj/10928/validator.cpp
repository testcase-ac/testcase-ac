#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string S: 1 to 50 characters, only uppercase, lowercase letters and digits
    inf.readToken("[A-Za-z0-9]{1,50}", "S");
    // The token must be followed by exactly one newline
    inf.readEoln();
    // No extra content after this
    inf.readEof();

    return 0;
}
