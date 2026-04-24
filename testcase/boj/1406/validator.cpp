#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read initial string: only lowercase letters, length up to 100000 (empty allowed)
    // Using a permissive regex then enforcing length bound.
    string initial = inf.readLine("[a-z]*", "initial_string");
    int N = initial.length();
    ensuref(N <= 100000,
            "Initial string length %d exceeds limit 100000", N);
    // Capacity constraint: editor holds up to 600000 characters at any time
    long long cur_len = N;
    ensuref(cur_len <= 600000,
            "Initial string length %d exceeds capacity 600000", N);

    // Read number of commands M: 1 <= M <= 500000
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read and validate each command, simulating length changes
    for (int i = 0; i < M; i++) {
        // Read the entire line, then check its format manually
        string cmd = inf.readLine("[^]+", "command");
        if (cmd == "L" || cmd == "D") {
            // move commands, no length change
        }
        else if (cmd == "B") {
            // delete left character if any
            if (cur_len > 0) {
                cur_len--;
            }
        }
        else {
            // must be of form "P x" where x is a lowercase letter
            ensuref((int)cmd.size() == 3 && cmd[0] == 'P' && cmd[1] == ' '
                    && cmd[2] >= 'a' && cmd[2] <= 'z',
                    "Invalid insert command at line %d: \"%s\"",
                    i + 3, cmd.c_str());
            // insertion increases length by 1
            cur_len++;
            ensuref(cur_len <= 600000,
                    "Exceeded capacity at command %d: length %lld",
                    i + 1, cur_len);
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
