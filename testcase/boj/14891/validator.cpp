#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four gear states, each is an 8-character string of '0' or '1'
    inf.readLine("[01]{8}", "gear1");
    inf.readLine("[01]{8}", "gear2");
    inf.readLine("[01]{8}", "gear3");
    inf.readLine("[01]{8}", "gear4");

    // Number of rotations K
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Read each rotation operation
    for (int i = 1; i <= K; i++) {
        int gear_num = inf.readInt(1, 4, "gear_num");
        inf.readSpace();
        int dir = inf.readInt(-1, 1, "dir");
        // dir must be exactly -1 or 1 (readInt allows -1,0,1)
        ensuref(dir != 0,
                "Invalid direction at operation %d: expected -1 or 1, found %d", i, dir);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
