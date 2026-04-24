#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cows
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read coordinates for each cow
    for (int i = 0; i < N; i++) {
        // Each line has exactly two integers: x and y
        vector<int> coord = inf.readInts(2, 0, 25000, "coord");
        // coord[0] is x_i, coord[1] is y_i
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
