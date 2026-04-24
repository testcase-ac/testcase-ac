#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 7, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Second line: N natural numbers (1 to 10000)
    vector<int> a = inf.readInts(N, 1, 10000, "a_i");
    inf.readEoln();

    // No further content
    inf.readEof();
    return 0;
}
