#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(m, 1, 100, "a_i");
    inf.readEoln();

    inf.readEof();
}
