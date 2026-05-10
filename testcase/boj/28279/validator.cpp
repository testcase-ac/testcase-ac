#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of commands
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    bool seen_output = false;
    for (int i = 0; i < N; i++) {
        // Read command code
        int cmd = inf.readInt(1, 8, "command");
        if (cmd == 1 || cmd == 2) {
            // Commands 1 and 2 have an argument X
            inf.readSpace();
            inf.readInt(1, 100000, "X");
            inf.readEoln();
        } else {
            // Commands 3 to 8 should be alone on the line
            inf.readEoln();
            // Commands 3,4,5,6,7,8 all produce output
            seen_output = true;
        }
    }

    // Ensure at least one output-producing command exists
    ensuref(seen_output,
            "Input must contain at least one output-producing command (3, 4, 5, 6, 7, or 8)");

    inf.readEof();
    return 0;
}
