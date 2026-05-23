#include "testlib.h"
using namespace std;

static const long long MAX_INITIAL_VALUE = 1000000000000000000LL - 1;
static const long long MAX_QUERY_INDEX = 1000000000000000000LL;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    inf.readLongs(k, 0LL, MAX_INITIAL_VALUE, "a_i");
    inf.readEoln();

    int q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        long long l = inf.readLong(1LL, MAX_QUERY_INDEX, "l_i");
        inf.readSpace();
        long long r = inf.readLong(1LL, MAX_QUERY_INDEX, "r_i");
        inf.readEoln();
        ensuref(l <= r, "query %d has l_i > r_i: %lld > %lld", i + 1, l, r);
    }

    inf.readEof();
}
