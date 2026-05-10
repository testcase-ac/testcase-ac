#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of players
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Each of the next N lines contains exactly 4 dice rolls in [1,6]
    for (int i = 0; i < N; i++) {
        vector<int> dice = inf.readInts(4, 1, 6, "dice");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
