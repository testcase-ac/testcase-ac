#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read the sequence T[1..n], each between 0 and 999999 inclusive
    vector<int> T = inf.readInts(n, 0, 999999, "T_i");
    inf.readEoln();

    // No extra data allowed
    inf.readEof();
    return 0;
}
