#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read N
    for (int i = 0; i < T; i++) {
        // N: number of cards in this game
        inf.readInt(1, 5000000, "N");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
