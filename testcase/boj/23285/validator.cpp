#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readEoln();

    vector<int> sequence = inf.readInts(n - 2, 1, n, "sequence");
    (void)sequence;
    inf.readEoln();

    inf.readEof();
}
