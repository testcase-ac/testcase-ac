#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // 2. Read T lines of gear states
    for (int i = 0; i < T; ++i) {
        string s = inf.readToken("[01]{8}", "gear_state");
        inf.readEoln();
        // No further validation needed, as regex ensures 8 chars of '0' or '1'
    }

    // 3. Read K
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // 4. Read K lines of (gear_num, dir)
    for (int i = 0; i < K; ++i) {
        int gear_num = inf.readInt(1, T, "gear_num");
        inf.readSpace();
        int dir = inf.readInt(-1, 1, "dir");
        inf.readEoln();
        ensuref(dir == 1 || dir == -1, "dir must be 1 or -1, but got %d at line %d", dir, i+T+3);
    }

    inf.readEof();
}
