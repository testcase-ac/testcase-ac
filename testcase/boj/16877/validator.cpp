#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of piles
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read P_i: number of stones in each pile
    vector<int> P = inf.readInts(N, 1, 3000000, "P_i");
    inf.readEoln();

    inf.readEof();
}
