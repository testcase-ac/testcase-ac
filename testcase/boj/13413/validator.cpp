#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read N
        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        // Read initial state
        string init = inf.readToken("[WB]+", "initial_state");
        inf.readEoln();
        ensuref((int)init.size() == N,
                "Length of initial_state (%d) does not match N (%d) in test case %d",
                (int)init.size(), N, tc);

        // Read target state
        string target = inf.readToken("[WB]+", "target_state");
        inf.readEoln();
        ensuref((int)target.size() == N,
                "Length of target_state (%d) does not match N (%d) in test case %d",
                (int)target.size(), N, tc);
    }

    inf.readEof();
    return 0;
}
