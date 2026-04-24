#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 10000, "L");
    inf.readEoln();

    // Read fruit heights
    vector<int> h = inf.readInts(n, 1, 10000, "h_i");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
