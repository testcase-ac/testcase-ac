#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the sequence of dolls: 1 or 2
    vector<int> dolls = inf.readInts(N, 1, 2, "doll_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
