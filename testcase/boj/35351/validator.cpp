#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> pow3(13, 1);
    for (int i = 1; i <= 12; ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }

    int n = inf.readInt(1, 12, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    int len = pow3[n];
    string t = inf.readToken("[AB]{1,531441}", "T");
    ensuref((int)t.size() == len, "T length must be 3^N: expected %d, found %d", len, (int)t.size());
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, len, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
