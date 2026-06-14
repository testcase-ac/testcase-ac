#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    set<int> seen(a.begin(), a.end());
    ensuref(static_cast<int>(seen.size()) == n, "array A must contain distinct values");

    inf.readInts(n, 1, 1000000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
