#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 999, "A_i");
    inf.readEoln();

    inf.readEof();
}
