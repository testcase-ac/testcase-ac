#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(n, 1LL, 1000000000LL, "b_i");
    inf.readEoln();

    set<long long> seenA(a.begin(), a.end());
    ensuref((int)seenA.size() == n, "array A must contain distinct values");

    set<long long> seenB(b.begin(), b.end());
    ensuref((int)seenB.size() == n, "array B must contain distinct values");

    inf.readEof();
}
