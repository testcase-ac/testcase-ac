#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 500000, "K");
    inf.readEoln();

    // Read the sequence of K device usages
    vector<int> usages = inf.readInts(K, 1, K, "device_usage");
    inf.readEoln();

    // No other global constraints to check
    inf.readEof();
    return 0;
}
