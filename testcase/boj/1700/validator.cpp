#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Read the sequence of K usages
    vector<int> usage = inf.readInts(K, 1, K, "usage");
    inf.readEoln();

    // No further content
    inf.readEof();
    return 0;
}
