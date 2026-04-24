#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the digit string S: length between 1 and 40, digits only
    string s = inf.readToken("[0-9]{1,40}", "s");
    // End of line after the string
    inf.readEoln();
    // No further content
    inf.readEof();
    return 0;
}
