#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;
    const int MAX_A = (1 << 20) - 1;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, MAX_A, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
