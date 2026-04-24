#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of rounds
    int n = inf.readInt(1, 15, "n");
    inf.readEoln();

    // Each round: two dice rolls between 1 and 6
    for (int i = 0; i < n; i++) {
        int c = inf.readInt(1, 6, "c_i"); // 창영이's roll
        inf.readSpace();
        int s = inf.readInt(1, 6, "s_i"); // 상덕이's roll
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
