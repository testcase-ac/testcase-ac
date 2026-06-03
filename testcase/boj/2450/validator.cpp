#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    vector<int> shapes = inf.readInts(n, 1, 3, "shape");
    inf.readEoln();

    array<int, 4> count{};
    for (int shape : shapes) {
        ++count[shape];
    }

    for (int shape = 1; shape <= 3; ++shape) {
        ensuref(count[shape] > 0, "shape %d must appear at least once", shape);
    }

    inf.readEof();
}
