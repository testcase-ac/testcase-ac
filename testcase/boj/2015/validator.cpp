#include "testlib.h"
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(-2000000000, 2000000000, "K");
    inf.readEoln();

    // 2. Read A[1..N]
    vector<int> A = inf.readInts(N, -10000, 10000, "A_i");
    inf.readEoln();

    // 3. Global formatting: EOF after input
    inf.readEof();

    // 4. No further global constraints in the statement (e.g., no guarantee that answer exists, etc.)
    //    No need to check for leading zeros since numbers are read as ints.
    //    No need to check for other properties.

    return 0;
}
