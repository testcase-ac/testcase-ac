#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> oil = inf.readInts(n, 1, 1000000, "o_i");
    inf.readEoln();

    vector<int> distance = inf.readInts(n, 1, 1000000, "d_i");
    inf.readEoln();

    long long oil_sum = accumulate(oil.begin(), oil.end(), 0LL);
    long long distance_sum = accumulate(distance.begin(), distance.end(), 0LL);
    ensuref(oil_sum == distance_sum,
            "sum(o_i) must equal sum(d_i): %lld != %lld",
            oil_sum,
            distance_sum);

    inf.readEof();
}
