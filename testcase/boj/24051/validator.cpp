#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1LL * n * n, "K");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    set<long long> seen(a.begin(), a.end());
    ensuref(static_cast<int>(seen.size()) == n, "A_i values must be distinct");

    inf.readEof();
}
