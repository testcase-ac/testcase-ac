#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 123, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();
    vector<int> seen(n + 1, 0);
    for (int x : a) {
        ensuref(++seen[x] == 1, "disk radius %d appears more than once", x);
    }

    inf.readEof();
}
