#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 5000, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 0, 1, "b_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
