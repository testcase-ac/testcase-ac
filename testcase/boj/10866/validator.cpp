#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of commands
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Valid command names
    auto isNoArg = [&](const string &s) {
        return s == "pop_front" || s == "pop_back"
            || s == "size"      || s == "empty"
            || s == "front"     || s == "back";
    };
    auto isPush = [&](const string &s) {
        return s == "push_front" || s == "push_back";
    };

    // Process each command line
    for (int i = 0; i < N; i++) {
        // Read the command token (only lowercase and underscore)
        string cmd = inf.readToken("[a-z_]+", "cmd");
        if (isPush(cmd)) {
            // Must have exactly one space then integer X
            inf.readSpace();
            inf.readInt(1, 100000, "X");
            inf.readEoln();
        }
        else if (isNoArg(cmd)) {
            // No-argument commands must end immediately
            inf.readEoln();
        }
        else {
            // Invalid command name
            ensuref(false,
                    "Invalid command '%s' at line %d",
                    cmd.c_str(), i + 2);
        }
    }

    inf.readEof();
    return 0;
}
