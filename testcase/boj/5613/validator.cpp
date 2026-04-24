#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the initial number
    long long current = inf.readInt(1, 100000000, "number");
    inf.readEoln();

    // Then we have lines: operator, (if not '=' then operand), until '='
    while (true) {
        // Read operator: one of + - * / =
        string op = inf.readToken("[-+*/=]", "op");
        inf.readEoln();

        // If it's '=', we stop processing
        if (op == "=") {
            break;
        }

        // Otherwise, it must be one of the four arithmetic ops
        // Read the next operand
        long long y = inf.readInt(1, 100000000, "operand");
        inf.readEoln();

        // Perform the operation, checking any implied constraints
        if (op == "+") {
            current += y;
        } else if (op == "-") {
            current -= y;
        } else if (op == "*") {
            current = current * y;
        } else if (op == "/") {
            // The problem guarantees we never divide when the current value is negative
            ensuref(current >= 0, "Division by %lld when current value is negative (%lld)", y, current);
            current = current / y; // integer division truncates toward zero
        } else {
            // Should never happen due to regex, but just in case
            ensuref(false, "Unknown operator '%s'", op.c_str());
        }

        // After each operation, result must stay within [-1e8, 1e8]
        ensuref(current >= -100000000 && current <= 100000000,
                "Intermediate result %lld out of bounds [-1e8,1e8]", current);
    }

    // After reading '=', the file must end
    inf.readEof();
    return 0;
}
