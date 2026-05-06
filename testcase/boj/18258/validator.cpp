#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of commands N
    int N = inf.readInt(1, 2000000, "N");
    inf.readEoln();

    // Process each of the N commands
    for (int i = 0; i < N; i++) {
        // Read the command token
        string cmd = inf.readToken("push|pop|size|empty|front|back", "command");

        if (cmd == "push") {
            // After "push" there must be exactly one space, then an integer X, then newline
            inf.readSpace();
            inf.readInt(1, 100000, "X");
            inf.readEoln();
        } else {
            // For the other commands, no extra token is allowed
            inf.readEoln();
        }
    }

    // No extra data after processing all commands
    inf.readEof();
    return 0;
}
