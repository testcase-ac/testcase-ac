#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(n, 1LL, 1000000000LL, "b_i");
    inf.readEoln();

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ensuref(a == b, "b must be a rearrangement of a");

    inf.readEof();
}
