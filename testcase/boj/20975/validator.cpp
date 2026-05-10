#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read a_1..a_N
    vector<int> a = inf.readInts(N, 1, 1000000000, "a_i");
    inf.readEoln();

    // Read b_1..b_N
    vector<int> b = inf.readInts(N, 1, 1000000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
