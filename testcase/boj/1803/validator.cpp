#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 50000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(m, 1, n, "A_destination");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 1, m, "B_destination");
    inf.readEoln();

    inf.readEof();
    return 0;
}
