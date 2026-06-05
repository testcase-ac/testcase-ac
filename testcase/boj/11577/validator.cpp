#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 0, 1, "s_i");
    inf.readEoln();

    inf.readEof();
}
