#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of segments
    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    // Read the lengths of the n segments
    vector<int> a = inf.readInts(n, 1, 20000, "segment_length");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
