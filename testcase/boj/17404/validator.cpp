#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of houses
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // For each house, three painting costs: red, green, blue
    for (int i = 0; i < N; i++) {
        // Read three positive costs ≤ 1000
        inf.readInt(1, 1000, "cost1");
        inf.readSpace();
        inf.readInt(1, 1000, "cost2");
        inf.readSpace();
        inf.readInt(1, 1000, "cost3");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
