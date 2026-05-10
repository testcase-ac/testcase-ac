#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Read sequence a_1 ... a_N
    vector<int> a = inf.readInts(N, 1, 100000, "a_i");
    inf.readEoln();

    inf.readEof();
}
