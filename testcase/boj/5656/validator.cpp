#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    bool seen_end = false;

    // Read lines until we see the termination operator 'E'
    while (true) {
        lines++;
        // Check line count limit
        ensuref(lines <= 12000, "Number of lines %d exceeds limit of 12000", lines);

        // Read left operand
        int a = inf.readInt(-10000, 10000, "a");
        inf.readSpace();

        // Read operator token
        string op = inf.readToken(">=|<=|==|!=|>|<|E", "op");
        inf.readSpace();

        // Read right operand
        int b = inf.readInt(-10000, 10000, "b");
        inf.readEoln();

        // Check for termination operator
        if (op == "E") {
            seen_end = true;
            break;
        }
        // Otherwise op must be one of the 6 comparison operators (ensured by regex)
    }

    // Ensure we encountered exactly one termination line
    ensuref(seen_end, "No termination operator 'E' found in input");

    // After reading the terminating line, there must be nothing else
    inf.readEof();
    return 0;
}
