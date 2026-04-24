#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    // Read the dependency array x_i
    vector<int> x = inf.readInts(n, 1, n, "x_i");
    inf.readEoln();

    // No other global constraints to check
    inf.readEof();
    return 0;
}
