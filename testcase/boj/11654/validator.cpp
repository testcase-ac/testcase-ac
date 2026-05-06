#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly one character on the first line: must be a lowercase letter,
    // uppercase letter, or digit.
    inf.readLine("[a-zA-Z0-9]", "c");

    // No extra content: immediately EOF after that one newline.
    inf.readEof();
    return 0;
}
