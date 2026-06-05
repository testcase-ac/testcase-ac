#include "testlib.h"

#include <string>

using namespace std;

static string readOperation(const string& name) {
    string op = inf.readToken("[^ ]{2,2}", name);
    ensuref(op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/',
            "%s has invalid operator: %c", name.c_str(), op[0]);
    ensuref('1' <= op[1] && op[1] <= '9',
            "%s has invalid operand: %c", name.c_str(), op[1]);
    return op;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        readOperation("left");
        inf.readSpace();
        readOperation("right");
        inf.readEoln();
    }

    inf.readEof();
}
