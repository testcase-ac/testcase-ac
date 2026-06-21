#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 1000, "A");
    inf.readEoln();

    inf.readEof();
}
