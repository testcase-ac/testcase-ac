#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read N positions
    vector<int> pos = inf.readInts(N, -10000, 10000, "book_position");
    inf.readEoln();

    // Check that no position is 0
    for (int i = 0; i < N; ++i) {
        ensuref(pos[i] != 0, "Book position at index %d is 0, but must be nonzero.", i+1);
    }

    inf.readEof();
}
