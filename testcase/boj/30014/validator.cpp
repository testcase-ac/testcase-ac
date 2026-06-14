#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 1, 1000, "P_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
