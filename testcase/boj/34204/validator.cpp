#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, C
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // No further global constraints in the statement (e.g., no duplicates, no sortedness, etc.)
    // No further global properties to check (e.g., answer always exists is implied by constraints).

    inf.readEof();
}
