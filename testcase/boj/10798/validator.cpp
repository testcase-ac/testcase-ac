#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 5 lines, each is a word of length 1 to 15,
    // consisting only of A-Z, a-z, 0-9, with no spaces.
    for (int i = 1; i <= 5; i++) {
        string name = "s_" + to_string(i);
        // readToken stops at whitespace, so no spaces are allowed within the word
        inf.readToken("[A-Za-z0-9]{1,15}", name.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
