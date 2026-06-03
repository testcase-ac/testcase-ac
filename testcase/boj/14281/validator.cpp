#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 1000000000, "a_i");
    inf.readEoln();

    inf.readEof();
}
