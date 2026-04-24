#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of participants
    int N = inf.readInt(2, 200, "N");
    inf.readEoln();

    // Each of N lines: three integers between 1 and 100
    for (int i = 1; i <= N; i++) {
        inf.readInts(3, 1, 100, "score");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
