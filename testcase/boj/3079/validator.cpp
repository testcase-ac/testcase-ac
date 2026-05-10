#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000000LL, "M");
    inf.readEoln();

    // Read T_k
    vector<long long> T(N);
    set<long long> seen;
    for (int i = 0; i < N; ++i) {
        T[i] = inf.readLong(1LL, 1000000000LL, "T_k");
        inf.readEoln();
    }

    inf.readEof();
}
