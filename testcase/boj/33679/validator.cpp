#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of bullets
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // YJ's bullets
    vector<int> A = inf.readInts(N, 1, 100000000, "A_i");
    inf.readEoln();

    // HG's bullets
    vector<int> B = inf.readInts(N, 1, 100000000, "B_i");
    inf.readEoln();

    inf.readEof();
}
