#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of commands N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    bool hasOutputCommand = false;
    for (int i = 0; i < N; i++) {
        // Read command type t
        int t = inf.readInt(1, 5, "cmd");
        if (t == 1) {
            // Command "1 X"
            inf.readSpace();
            inf.readInt(1, 100000, "X");
        } else {
            // Commands 2,3,4,5 require output
            hasOutputCommand = true;
        }
        // No extra tokens or spaces allowed: must end line here
        inf.readEoln();
    }

    // There must be at least one output command among the N commands
    ensuref(hasOutputCommand,
            "At least one output command (type 2, 3, 4, or 5) must be present");

    inf.readEof();
    return 0;
}
