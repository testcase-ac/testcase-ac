#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rings
    int n = inf.readInt(3, 100, "N");
    inf.readEoln();

    // Read radii
    vector<int> r = inf.readInts(n, 1, 1000, "radius");
    inf.readEoln();

    // No further data
    inf.readEof();
    return 0;
}
