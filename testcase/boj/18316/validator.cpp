#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    inf.readInt(1, 1000, "C");
    inf.readEoln();

    vector<int> moonies = inf.readInts(n, 0, 1000, "m_i");
    inf.readEoln();
    ensuref(moonies[0] == 0, "m_1 must be 0, found %d", moonies[0]);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "road %d is a self-loop: %d %d", i, a, b);
    }

    inf.readEof();
}
