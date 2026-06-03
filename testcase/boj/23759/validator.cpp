#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[a-z]{1,10}", "S_i");
        ensuref((int)s.size() == k, "S_%d has length %d, expected %d", i, (int)s.size(), k);
        inf.readEoln();
    }

    inf.readEof();
}
