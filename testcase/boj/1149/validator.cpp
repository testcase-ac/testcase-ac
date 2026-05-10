#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of houses
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // For each house, three painting costs (red, green, blue)
    for (int i = 1; i <= N; i++) {
        inf.readInts(3, 1, 1000, "costs");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
