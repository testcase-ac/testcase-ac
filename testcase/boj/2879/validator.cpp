#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lines N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read current tab counts
    vector<int> A = inf.readInts(N, 0, 80, "current_tabs");
    inf.readEoln();

    // Read target tab counts
    vector<int> B = inf.readInts(N, 0, 80, "target_tabs");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
