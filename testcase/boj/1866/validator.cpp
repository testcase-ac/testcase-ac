#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of packages N
    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();

    // Read destinations: N integers between 1 and 10000
    vector<int> dest = inf.readInts(N, 1, 10000, "dest_i");
    inf.readEoln();

    // Read truck cost per segment and helicopter cost per use
    int truck_cost = inf.readInt(1, 1000, "truck_cost");
    inf.readSpace();
    int helicopter_cost = inf.readInt(1, 1000, "helicopter_cost");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
