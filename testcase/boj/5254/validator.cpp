#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(3, 300000, "n");
    inf.readEoln();

    // Read c_i values
    vector<int> c = inf.readInts(n, -1000000000, 1000000000, "c_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
