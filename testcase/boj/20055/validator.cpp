#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 2 * N, "K");
    inf.readEoln();

    // Read the durability array A of length 2N
    vector<int> A = inf.readInts(2 * N, 1, 1000, "A");
    inf.readEoln();

    // No further global properties to check; simulation always terminates under the given constraints.
    inf.readEof();
    return 0;
}
