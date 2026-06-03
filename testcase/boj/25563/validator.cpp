#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_VALUE = 1000000;

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readInt(0, MAX_VALUE, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, MAX_VALUE, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
