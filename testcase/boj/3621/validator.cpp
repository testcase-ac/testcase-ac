#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int d = inf.readInt(2, n, "d");
    inf.readEoln();

    vector<int> child = inf.readInts(n, 0, n, "child");
    inf.readEoln();
    inf.readEof();
}
