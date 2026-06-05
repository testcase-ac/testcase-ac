#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100000000, "k");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    set<int> seen(a.begin(), a.end());
    ensuref((int)seen.size() == n, "array elements must be distinct");

    inf.readEof();
}
