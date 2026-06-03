#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(0, 100000, "K");
    inf.readEoln();

    vector<int> caffeine = inf.readInts(n, 1, 1000, "C_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
