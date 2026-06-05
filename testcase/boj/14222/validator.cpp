#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    inf.readInt(1, 10, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 50, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
