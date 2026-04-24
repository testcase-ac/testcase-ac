#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string: must be 1 to 10000 uppercase letters A-Z
    inf.readToken("[A-Z]{1,10000}", "S");
    // Exactly one newline after the string
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
