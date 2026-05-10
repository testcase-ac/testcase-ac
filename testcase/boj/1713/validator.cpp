#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of photo frames
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Total number of recommendations
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Recommendation sequence
    vector<int> recs = inf.readInts(T, 1, 100, "rec");
    inf.readEoln();

    inf.readEof();
    return 0;
}
