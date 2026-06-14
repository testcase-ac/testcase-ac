#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readEoln();

    vector<int> weights = inf.readInts(n, 1, 10000, "W");
    inf.readEoln();

    inf.readEof();
    return 0;
}
