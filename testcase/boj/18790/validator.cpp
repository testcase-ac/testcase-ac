#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // 2. Read 2N-1 numbers, each in [0, N-1]
    int total = 2 * N - 1;
    vector<int> a = inf.readInts(total, 0, N - 1, "a_i");
    inf.readEoln();

    // 3. Check input size
    ensuref((int)a.size() == total, "Expected %d numbers, got %d", total, (int)a.size());

    // 4. Check EOF
    inf.readEof();
}
