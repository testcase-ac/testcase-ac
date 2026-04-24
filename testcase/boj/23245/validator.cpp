#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read sequence p
    vector<int> p = inf.readInts(n, 0, 1000000, "p_i");
    inf.readEoln();

    // Read sequence q
    vector<int> q = inf.readInts(n, 0, 1000000, "q_i");
    inf.readEoln();

    // No further global properties to validate for input
    inf.readEof();
    return 0;
}
