#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M"); // ensures 1 ≤ M ≤ N
    inf.readEoln();

    // Second line: N natural numbers ≤ 10000
    vector<int> a = inf.readInts(N, 1, 10000, "a");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
