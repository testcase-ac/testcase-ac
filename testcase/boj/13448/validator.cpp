#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Read M_i
    vector<int> M = inf.readInts(N, 1, 100000, "M_i");
    inf.readEoln();

    // Read P_i
    vector<int> P = inf.readInts(N, 1, 100000, "P_i");
    inf.readEoln();

    // Read R_i
    vector<int> R = inf.readInts(N, 1, 100000, "R_i");
    inf.readEoln();

    // No additional global constraints to check
    inf.readEof();
    return 0;
}
