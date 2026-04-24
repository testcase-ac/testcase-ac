#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of drivers
    int N = inf.readInt(3, 300000, "N");
    inf.readEoln();

    // Scores before the last race
    for (int i = 1; i <= N; i++) {
        // Each B_i must be between 0 and 2,000,000
        inf.readInt(0, 2000000, "B_i");
        inf.readEoln();
    }

    // No extra tokens
    inf.readEof();
    return 0;
}
