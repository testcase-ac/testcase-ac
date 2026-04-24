#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // Second line: a_1 ... a_N
    vector<int> a = inf.readInts(N, 0, 200000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
