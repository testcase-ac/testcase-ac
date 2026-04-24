#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of roads in each direction
    int N = inf.readInt(5, 1000, "N");
    inf.readEoln();

    // Read W: number of events
    int W = inf.readInt(1, 1000, "W");
    inf.readEoln();

    // Read each event location
    for (int i = 0; i < W; i++) {
        int x = inf.readInt(1, N, "row");
        inf.readSpace();
        int y = inf.readInt(1, N, "col");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
