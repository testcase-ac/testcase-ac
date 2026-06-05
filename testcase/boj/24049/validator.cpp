#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<int> left = inf.readInts(n, 0, 1, "left");
    inf.readEoln();

    vector<int> top = inf.readInts(m, 0, 1, "top");
    inf.readEoln();

    inf.readEof();
}
