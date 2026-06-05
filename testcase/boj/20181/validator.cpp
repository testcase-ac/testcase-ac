#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100000000, "k");
    inf.readEoln();

    vector<int> satisfaction = inf.readInts(n, 0, 100000000, "a_i");
    inf.readEoln();

    inf.readEof();
}
