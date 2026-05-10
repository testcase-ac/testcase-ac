#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(2, 100, "M");
    inf.readSpace();
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read M lines, each with N planet sizes
    for (int i = 0; i < M; ++i) {
        vector<int> planets = inf.readInts(N, 1, 1000000, "planet_size");
        inf.readEoln();
    }

    inf.readEof();
}
