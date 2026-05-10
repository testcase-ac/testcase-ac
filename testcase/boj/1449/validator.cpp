#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readEoln();

    // Read leak positions
    vector<int> leaks = inf.readInts(N, 1, 1000, "leak_position");
    inf.readEoln();

    // Check for duplicate leak positions
    set<int> leak_set(leaks.begin(), leaks.end());
    ensuref((int)leak_set.size() == N, "Duplicate leak positions are not allowed.");

    inf.readEof();
}
