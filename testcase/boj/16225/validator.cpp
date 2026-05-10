#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 200000, "N");
    ensuref(N % 2 == 0, "N must be even, but got %d", N);
    inf.readEoln();

    // Read A[1..N]
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Read B[1..N]
    vector<int> B = inf.readInts(N, 1, 1000000000, "B_i");
    inf.readEoln();

    // Check all A[i] are distinct
    set<int> setA(A.begin(), A.end());
    ensuref((int)setA.size() == N, "All A[i] must be distinct, but found duplicates");

    // Check all B[i] are distinct
    set<int> setB(B.begin(), B.end());
    ensuref((int)setB.size() == N, "All B[i] must be distinct, but found duplicates");

    inf.readEof();
}
