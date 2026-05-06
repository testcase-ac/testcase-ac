#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of log records
    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    // Each record: name and operation
    for (int i = 0; i < n; i++) {
        // Name: 1 to 5 letters, upper or lower case
        inf.readToken("[a-zA-Z]{1,5}", "name");
        // Exactly one space before operation
        inf.readSpace();
        // Operation: either "enter" or "leave"
        inf.readToken("enter|leave", "op");
        // End of line
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
