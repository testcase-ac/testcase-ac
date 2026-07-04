#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of instances; this cap
    // keeps the input size practical while allowing the maximum scalar scale.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long instructionCount = 0;
    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 50, "m");
        inf.readSpace();
        int t = inf.readInt(1, 40, "T");
        inf.readEoln();

        instructionCount += m;
        ensuref(instructionCount <= 5000000LL,
                "total instruction count exceeds practical cap: %lld",
                instructionCount);

        for (int i = 1; i <= m; ++i) {
            string op = inf.readToken("[+\\-]?[0-9]+|L", "instruction");

            if (op == "L") {
                // Lose a turn.
            } else if (op == "0") {
                // No instruction.
            } else {
                ensuref(op[0] == '+' || op[0] == '-',
                        "instruction %d must be +n, -n, L, or 0: %s",
                        i, op.c_str());
                ensuref(op.size() >= 2, "missing move amount at instruction %d", i);
                ensuref(op[1] != '0',
                        "move amount must be positive and canonical at instruction %d: %s",
                        i, op.c_str());

                int amount = 0;
                for (int j = 1; j < int(op.size()); ++j) {
                    ensuref('0' <= op[j] && op[j] <= '9',
                            "invalid move amount at instruction %d: %s",
                            i, op.c_str());
                    amount = amount * 10 + (op[j] - '0');
                    ensuref(amount <= 51,
                            "move amount too large to stay on board at instruction %d: %s",
                            i, op.c_str());
                }

                int target = op[0] == '+' ? i + amount : i - amount;
                ensuref(0 <= target && target <= m + 1,
                        "instruction %d moves off the board: %s", i, op.c_str());
            }

            if (i == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
