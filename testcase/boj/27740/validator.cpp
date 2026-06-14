#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 300000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 1, "a_i");
    inf.readEoln();

    bool hasOne = false;
    for (int value : a) {
        hasOne = hasOne || value == 1;
    }
    ensuref(hasOne, "the sequence must contain at least one 1");

    inf.readEof();
}
