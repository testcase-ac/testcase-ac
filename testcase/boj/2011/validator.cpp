#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the encoded string: must be 1 to 5000 digits, no other characters
    inf.readToken("[0-9]{1,5000}", "s");
    // There must be exactly one newline after the string
    inf.readEoln();
    // And nothing else in the file
    inf.readEof();

    return 0;
}
