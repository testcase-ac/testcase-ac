#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "A_i");
    (void)a;
    inf.readEoln();

    inf.readEof();
    return 0;
}
