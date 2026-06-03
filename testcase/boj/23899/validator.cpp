#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 1, 1000000000, "b_i");
    inf.readEoln();

    set<int> seen_a(a.begin(), a.end());
    ensuref((int)seen_a.size() == n, "array A must contain distinct values");

    set<int> seen_b(b.begin(), b.end());
    ensuref((int)seen_b.size() == n, "array B must contain distinct values");

    inf.readEof();
}
