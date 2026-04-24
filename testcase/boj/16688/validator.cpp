#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k"); // ensures 1 ≤ k ≤ n
    inf.readEoln();

    // Read difficulties
    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
