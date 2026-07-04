#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(n, n * n, "m");
    inf.readSpace();
    int k = inf.readInt(n, n * n, "k");
    inf.readEoln();

    vector<int> t = inf.readInts(m, 1, n, "t_i");
    inf.readEoln();

    vector<int> s = inf.readInts(k, 1, n, "s_i");
    inf.readEoln();

    long long requiredBattles = 1LL * n * n;
    long long kangarooBattles = accumulate(t.begin(), t.end(), 0LL);
    long long kiwiBattles = accumulate(s.begin(), s.end(), 0LL);

    ensuref(kangarooBattles == requiredBattles,
            "sum of t_i is %lld, expected %lld",
            kangarooBattles,
            requiredBattles);
    ensuref(kiwiBattles == requiredBattles,
            "sum of s_i is %lld, expected %lld",
            kiwiBattles,
            requiredBattles);

    inf.readEof();
    return 0;
}
