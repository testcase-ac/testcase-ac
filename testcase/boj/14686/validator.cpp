#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> swifts = inf.readInts(N, 0, 20, "swifts_runs");
    inf.readEoln();

    vector<int> semaphores = inf.readInts(N, 0, 20, "semaphores_runs");
    inf.readEoln();

    // Optional: we could verify that sums fit in int, but bounds guarantee it:
    // max sum per team = 20 * 100000 = 2,000,000 (safe in int)

    inf.readEof();
}
