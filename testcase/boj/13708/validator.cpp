#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(2, 300, "N");
    inf.readEoln();

    // Read N points
    for (int i = 0; i < N; i++) {
        // read two integers x, y in [0,1000]
        vector<int> xy = inf.readInts(2, 0, 1000, "xy");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
