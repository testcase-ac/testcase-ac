#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<long long> difficulties = inf.readLongs(n, 1LL, 1000000000LL, "difficulty");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(x, n, "y");
        inf.readEoln();
    }

    inf.readEof();
}
