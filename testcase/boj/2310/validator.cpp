#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read number of rooms (n), allowing 0 to terminate
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();
        if (n == 0) break;

        // New test case
        tc++;
        setTestCase(tc);
        ensuref(tc <= 100000, "Number of test cases exceeded the limit: %d", tc);

        // Validate each room
        for (int i = 1; i <= n; i++) {
            // Room type: E, L, or T
            string type = inf.readToken("[ELT]", "type");
            inf.readSpace();

            // Amount: 0 for E, [1,500] for L or T
            int amount;
            if (type == "E") {
                amount = inf.readInt(0, 0, "amount");
            } else {
                amount = inf.readInt(1, 500, "amount");
            }

            // Doors: sequence of integers in [1,n], terminated by a 0
            while (true) {
                inf.readSpace();
                int to = inf.readInt(0, n, "door");
                if (to == 0) {
                    break;
                }
                // no further checks on edges (loops/multiples allowed)
            }

            // End of this room's line
            inf.readEoln();
        }
    }

    // Entire file must end exactly here
    inf.readEof();
    return 0;
}
