#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 300000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    // Read the array a of size n, each 1 <= a_i <= 1e8
    vector<int> a = inf.readInts(n, 1, 100000000, "a_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
