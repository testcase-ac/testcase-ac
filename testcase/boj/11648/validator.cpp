#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input number as a token: 1 to 9 digits
    string s = inf.readToken("[0-9]{1,9}", "s");
    // The number must not have leading zeros, unless it is exactly "0"
    if (s.size() > 1) {
        ensuref(s[0] != '0',
                "The input has leading zero in a multi-digit number: \"%s\"", s.c_str());
    }
    // End of line after the number
    inf.readEoln();
    // No extra data in the file
    inf.readEof();

    return 0;
}
