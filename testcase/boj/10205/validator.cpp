#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of datasets K
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int tc = 1; tc <= K; tc++) {
        setTestCase(tc);

        // Read initial number of heads
        int h = inf.readInt(1, 50, "h");
        inf.readEoln();

        // Read action string: only 'c' and 'b', length between 0 and 100
        string actions = inf.readLine("[cb]{0,100}", "actions");

        // Validate the hydra process: no actions after heads reach zero
        long long cur = h;
        int n = (int)actions.size();
        for (int i = 0; i < n; i++) {
            char c = actions[i];
            // Apply action
            if (c == 'c') {
                // cut without burning: -1 + 2 = +1
                cur += 1;
            } else {
                // 'b': cut with burning: -1
                cur -= 1;
            }
            // Heads must never go negative
            ensuref(cur >= 0, "At dataset %d, action %d: head count negative (%lld)", tc, i+1, cur);

            // If heads reach zero, this must be the last action
            if (cur == 0 && i + 1 < n) {
                ensuref(false,
                        "At dataset %d, action %d: head count zero before end of actions, but more actions remain",
                        tc, i+1);
            }
        }
        // After processing all actions, cur >= 0 is ensured already.

        // Next dataset or end
    }

    inf.readEof();
    return 0;
}
