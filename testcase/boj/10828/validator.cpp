#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of commands
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read the command keyword
        string cmd = inf.readToken("[a-z]+", "cmd");

        if (cmd == "push") {
            // Expect exactly one space, then an integer X
            inf.readSpace();
            int X = inf.readInt(1, 100000, "X");
            inf.readEoln();
        } else if (cmd == "pop" || cmd == "size" || cmd == "empty" || cmd == "top") {
            // No extra tokens or spaces allowed
            inf.readEoln();
        } else {
            // Invalid command
            ensuref(false, "Invalid command at line %d: '%s'", i+2, cmd.c_str());
        }
    }

    inf.readEof();
    return 0;
}
