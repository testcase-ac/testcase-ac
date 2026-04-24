#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the array a of size N
    vector<int> a = inf.readInts(N, 0, 1000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
