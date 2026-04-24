#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // All values must be non-zero (acidic: 1..1e9, alkaline: -1..-1e9)
    for (int i = 0; i < n; ++i) {
        ensuref(a[i] != 0LL, "Value at position %d is 0; all solutions must be acidic (>=1) or alkaline (<=-1)", i + 1);
    }

    // Distinctness
    {
        set<long long> st(a.begin(), a.end());
        ensuref((int)st.size() == n, "Duplicate values detected among the %d solution characteristics (expected all distinct)", n);
    }

    inf.readEof();
}
