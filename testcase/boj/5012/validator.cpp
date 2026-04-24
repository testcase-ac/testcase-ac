#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the sequence of length n, each between 1 and n
    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
