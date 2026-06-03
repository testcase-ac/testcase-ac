#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The prose says N > 2, but the formal input bounds say 2 <= N.
    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    // CHECK: The prose calls A positive, but the formal input bounds allow 0.
    vector<int> a = inf.readInts(n, 0, 700000000, "A_i");
    inf.readEoln();

    inf.readEof();
}
