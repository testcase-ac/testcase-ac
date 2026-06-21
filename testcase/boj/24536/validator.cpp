#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    string directions = inf.readToken("[LR]{1,300000}", "directions");
    inf.readEoln();
    ensuref((int)directions.size() == n,
            "directions length is %d, expected %d",
            (int)directions.size(),
            n);

    vector<long long> heights = inf.readLongs(n, 1LL, 1000000000LL, "H_i");
    (void)heights;
    inf.readEoln();

    inf.readEof();
    return 0;
}
