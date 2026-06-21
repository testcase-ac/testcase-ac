#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 1, 1000000000, "P_i");
    inf.readEoln();
    inf.readEof();
}
