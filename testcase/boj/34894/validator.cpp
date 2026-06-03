#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 300000, "N");
    inf.readEoln();

    string s = inf.readToken("[UOSPC]{5,300000}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n,
            (int)s.size());
    inf.readEoln();

    vector<long long> costs = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    (void)costs;
    inf.readEoln();

    inf.readEof();
}
