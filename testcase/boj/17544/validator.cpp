#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readSpace();
    int K = inf.readInt(0, R - 1, "K");
    inf.readEoln();

    for (int i = 0; i < R; ++i) {
        vector<long long> row = inf.readLongs(C, 0LL, 1000000000LL, "H_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
