#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readEoln();

    vector<int> riceballs = inf.readInts(n, 1, 1000000, "riceball_size");
    inf.readEoln();

    inf.readEof();
}
