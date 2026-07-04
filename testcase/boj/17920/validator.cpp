#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100, "K");
    inf.readEoln();

    vector<int> prices = inf.readInts(n, 1, 100000, "price");
    inf.readEoln();

    inf.readEof();
}
