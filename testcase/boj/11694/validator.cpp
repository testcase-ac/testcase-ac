#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read P_i
    vector<int> P = inf.readInts(N, 1, 2000000000, "P_i");
    inf.readEoln();

    inf.readEof();
}
