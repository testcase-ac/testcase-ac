#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> h = inf.readInts(n, 0, 200000, "h_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
