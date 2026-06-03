#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, 300000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
