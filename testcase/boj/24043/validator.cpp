#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, (1 << 20) - 1, "a_i");
    (void)a;
    inf.readEoln();

    inf.readEof();
}
