#include "testlib.h"
#include <cctype>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire input as a single line (the program)
    string prog = inf.readLine("[A-Za-z]{1,200}", "program");
    inf.readEof();

    int n = prog.size();
    ensuref(n >= 1, "Program must have at least 1 character");

    // 1. Must start with a command (uppercase)
    ensuref(isupper(prog[0]), "Program must start with a command (uppercase letter)");

    // 2. Each command always has the same number of parameters
    // We'll parse the program, and for each command, record the number of parameters after it
    map<char, int> cmd_param_cnt;
    vector<pair<int, char>> cmd_pos; // (position, command)

    int i = 0;
    while (i < n) {
        // Must be a command
        ensuref(isupper(prog[i]), "Expected command (uppercase) at position %d, got '%c'", i, prog[i]);
        char cmd = prog[i];
        int j = i + 1;
        // Count parameters (lowercase letters) after the command
        int param_cnt = 0;
        while (j < n && islower(prog[j])) {
            ++param_cnt;
            ++j;
        }
        // Check for consistency
        if (cmd_param_cnt.count(cmd)) {
            ensuref(cmd_param_cnt[cmd] == param_cnt,
                "Command '%c' at position %d has %d parameters, but previously seen with %d parameters",
                cmd, i, param_cnt, cmd_param_cnt[cmd]);
        } else {
            cmd_param_cnt[cmd] = param_cnt;
        }
        cmd_pos.push_back({i, cmd});
        i = j;
        // If not at end, next must be a command
        if (i < n) {
            ensuref(isupper(prog[i]), "Expected command (uppercase) at position %d, got '%c'", i, prog[i]);
        }
    }

    // 3. No invalid characters
    for (int k = 0; k < n; ++k) {
        ensuref(isupper(prog[k]) || islower(prog[k]),
            "Invalid character at position %d: '%c'", k, prog[k]);
    }

    // 4. No empty commands (i.e., two commands in a row is allowed, since parameter count can be zero)
    // Already checked by parsing logic.

    // 5. No leading/trailing whitespace (already enforced by regex in readLine)

    // 6. No extra lines (already enforced by readEof)

    // 7. No empty input (already checked)

    // 8. Each command must always have the same number of parameters (already checked)

    // 9. Each command must be followed by its parameters (already checked)

    // 10. The program must be at most 200 characters (already checked by regex)

    // 11. Each command must have at least 0 parameters (already checked)

    // 12. The program must be a valid sequence of commands and parameters (already checked)

    // 13. No unnecessary leading zeros: not applicable

    // 14. No global property to check (e.g., answer always exists): not applicable

    // 15. No simulation required

    // 16. No NOPs in input (NOP is not part of input)

    // All checks passed
}
