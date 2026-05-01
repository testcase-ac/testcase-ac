#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read n natural numbers, each between 1 and 100000
    vector<int> a = inf.readInts(n, 1, 100000, "a_i");
    inf.readEoln();

    // Read k
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    // No extra global constraints in statement (e.g., no guarantee about answer bound),
    // so we don't need to compute or simulate anything here.

    inf.readEof();
}
