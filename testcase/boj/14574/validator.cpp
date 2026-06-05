#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    set<long long> skills;
    for (int i = 1; i <= n; ++i) {
        long long p = inf.readLong(0LL, 1000000000LL, "P_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "C_i");
        inf.readEoln();

        ensuref(skills.insert(p).second, "P_i values must be distinct: duplicate %lld at row %d", p, i);
    }

    inf.readEof();
}
