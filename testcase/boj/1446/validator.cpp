#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of shortcuts N and highway length D
    int N = inf.readInt(1, 12, "N");
    inf.readSpace();
    int D = inf.readInt(1, 10000, "D");
    inf.readEoln();

    // Read each shortcut
    for (int i = 0; i < N; i++) {
        int s = inf.readInt(0, 10000, "start_" + to_string(i));
        inf.readSpace();
        int e = inf.readInt(0, 10000, "end_" + to_string(i));
        inf.readSpace();
        int l = inf.readInt(0, 10000, "length_" + to_string(i));
        inf.readEoln();

        ensuref(s < e,
            "For shortcut index %d: start (%d) must be less than end (%d)", i, s, e);
    }

    inf.readEof();
    return 0;
}
