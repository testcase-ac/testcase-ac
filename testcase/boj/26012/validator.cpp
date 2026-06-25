#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 749, "n");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 1, 9999999, "p_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
