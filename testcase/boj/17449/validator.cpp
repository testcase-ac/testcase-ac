#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Tam-rep's mid-rank R
    int R = inf.readInt(1, 200000, "R");
    inf.readEoln();

    // Read number of participants after Tam-rep
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read the ranks of the next N participants
    inf.readInts(N, 1, 200000, "R_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
