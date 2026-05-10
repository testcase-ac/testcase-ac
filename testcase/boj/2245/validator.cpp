#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read A[1..N]
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // 3. Read B[1..N]
    vector<int> B = inf.readInts(N, 1, N, "B_i");
    inf.readEoln();

    // 4. No further global properties are implied by the problem statement.
    //    - There is no guarantee that the answer always exists.
    //    - The only constraints are that A and B are arrays of length N, with values in [1,N].

    inf.readEof();
}
