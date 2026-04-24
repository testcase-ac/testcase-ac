#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and n
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read n commands
    for (int i = 0; i < n; i++) {
        // Command name: either MOVE or TURN
        string cmd = inf.readToken("MOVE|TURN", "cmd");
        inf.readSpace();
        if (cmd == "MOVE") {
            // MOVE d, where 1 <= d <= 1000
            inf.readInt(1, 1000, "d");
        } else {
            // TURN dir, where dir is 0 or 1
            inf.readInt(0, 1, "dir");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
