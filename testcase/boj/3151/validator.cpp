#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read A_i
    vector<int> A = inf.readInts(N, -10000, 10000, "A_i");
    inf.readEoln();

    inf.readEof();
}
