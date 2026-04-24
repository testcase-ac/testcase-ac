#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Second line: a_i for Jimin's team
    vector<int> a = inf.readInts(N, 0, 50, "a_i");
    inf.readEoln();

    // Third line: b_j for Hansu's team
    vector<int> b = inf.readInts(M, 0, 50, "b_j");
    inf.readEoln();

    // No further content
    inf.readEof();
    return 0;
}
