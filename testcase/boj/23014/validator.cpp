#include "testlib.h"

using namespace std;

namespace {

const int MAX_T = 100;
const int SMALL_LIMIT = 1000;
const int LARGE_CASE_LIMIT = 10;
const int MAX_LARGE_N = 500000;
const int MAX_LARGE_Q = 100000;
const int MAX_S = 1000000000;
const long long MAX_VALUE = 1000000000000000000LL;

bool isPrime(int value) {
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (int divisor = 3; 1LL * divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, MAX_LARGE_N, "N");
        inf.readSpace();
        int q = inf.readInt(1, MAX_LARGE_Q, "Q");
        inf.readSpace();
        int p = inf.readInt(2, MAX_S, "P");
        inf.readEoln();

        ensuref(isPrime(p), "P must be prime, got %d", p);

        if (n > SMALL_LIMIT || q > SMALL_LIMIT) {
            ++largeCases;
            ensuref(largeCases <= LARGE_CASE_LIMIT,
                    "at most %d cases may exceed N,Q <= %d",
                    LARGE_CASE_LIMIT, SMALL_LIMIT);
        }

        inf.readLongs(n, 1LL, MAX_VALUE, "A_i");
        inf.readEoln();

        int type2Count = 0;
        for (int queryIndex = 1; queryIndex <= q; ++queryIndex) {
            int type = inf.readInt(1, 2, "query_type");
            inf.readSpace();

            if (type == 1) {
                int pos = inf.readInt(1, n, "pos");
                inf.readSpace();
                inf.readLong(1LL, MAX_VALUE, "val");
                inf.readEoln();
            } else {
                ++type2Count;
                inf.readInt(1, MAX_S, "S");
                inf.readSpace();
                int l = inf.readInt(1, n, "L");
                inf.readSpace();
                int r = inf.readInt(l, n, "R");
                inf.readEoln();
            }
        }

        ensuref(type2Count > 0, "test case %d must contain at least one type 2 query", tc);
    }

    inf.readEof();
}
