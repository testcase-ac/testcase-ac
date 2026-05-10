#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read S_i
    vector<int> S = inf.readInts(N, 1000, 1000000, "S_i");
    inf.readEoln();

    // No further global constraints in the problem statement.
    // No need to check for uniqueness, order, or other properties.

    inf.readEof();
}
