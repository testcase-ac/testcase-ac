#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readEoln();

    vector<int> c = inf.readInts(n, 1, 3000, "C_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
