#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> d = inf.readInts(n, 0, n - 1, "d");
    inf.readEoln();

    inf.readEof();
}
