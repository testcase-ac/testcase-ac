#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 1, 1000000, "s_i");
    inf.readEoln();

    inf.readEof();
}
