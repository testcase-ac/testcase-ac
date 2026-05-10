#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the sequence of length N
    vector<int> a = inf.readInts(N, 1, 100000, "A");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
