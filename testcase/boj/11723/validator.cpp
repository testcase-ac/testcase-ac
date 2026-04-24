#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of operations
    int M = inf.readInt(1, 3000000, "M");
    inf.readEoln();

    // Valid operation names
    const set<string> ops_with_arg = {"add", "remove", "check", "toggle"};
    const set<string> ops_no_arg = {"all", "empty"};

    for (int i = 0; i < M; i++) {
        // Read the entire line of operation
        string line = inf.readLine("[^]+", "operation");

        // Try to split into op and arg
        size_t pos = line.find(' ');
        if (pos == string::npos) {
            // No space: must be in ops_no_arg
            ensuref(ops_no_arg.count(line),
                    "Line %d: unknown or malformed operation '%s'; expected 'all' or 'empty'", 
                    i+2, line.c_str());
        } else {
            // There is a space: must be exactly one, and op must be in ops_with_arg
            ensuref(line.find(' ', pos+1) == string::npos,
                    "Line %d: too many spaces in operation '%s'", i+2, line.c_str());
            string op = line.substr(0, pos);
            string arg = line.substr(pos+1);
            ensuref(ops_with_arg.count(op),
                    "Line %d: unknown operation '%s'", i+2, op.c_str());
            // Arg must be an integer between 1 and 20, no leading zeros
            ensuref(!arg.empty() && arg[0] != '0',
                    "Line %d: argument missing or has leading zero in '%s'", i+2, line.c_str());
            // All characters must be digits
            for (char c : arg) {
                ensuref(c >= '0' && c <= '9',
                        "Line %d: non-digit character in argument '%s'", i+2, arg.c_str());
            }
            // Parse value and check range
            int x = 0;
            for (char c : arg) {
                x = x * 10 + (c - '0');
                // early bound check
                ensuref(x <= 20,
                        "Line %d: argument out of range in '%s'", i+2, line.c_str());
            }
            ensuref(1 <= x && x <= 20,
                    "Line %d: argument out of range in '%s'", i+2, line.c_str());
        }
    }

    inf.readEof();
    return 0;
}
