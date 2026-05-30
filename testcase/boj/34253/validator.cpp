#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 20, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[01]+", "S_i");
        ensuref((int)s.size() == k, "S_%d must have length %d, got %d", i, k, (int)s.size());
        inf.readEoln();
    }

    inf.readEof();
}
