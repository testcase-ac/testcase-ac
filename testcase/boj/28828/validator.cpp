#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

const int MAX_COUNT = 100000;
const int MAX_VALUE = 1000000000;
const long double LOG_LIMIT = 18.0L * logl(10.0L);
const long double LOG_EPS = 1e-7L;

long double sumLogs(const vector<int>& values) {
    long double result = 0.0L;
    for (int value : values) {
        result += logl((long double)value);
    }
    return result;
}

void ensureRatioAtMostLimitExactly(const vector<int>& a, const vector<int>& b) {
    cpp_int denominator = 1;
    for (int value : b) {
        denominator *= value;
    }

    cpp_int bound = denominator;
    bound *= 1000000000000000000LL;

    cpp_int numerator = 1;
    for (int value : a) {
        numerator *= value;
        ensuref(numerator <= bound,
                "product(a) / product(b) exceeds 10^18 while reading a_i");
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_COUNT, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAX_COUNT, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, MAX_VALUE, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(m, 1, MAX_VALUE, "b_i");
    inf.readEoln();

    long double logRatio = sumLogs(a) - sumLogs(b);
    if (fabsl(logRatio - LOG_LIMIT) <= LOG_EPS) {
        ensureRatioAtMostLimitExactly(a, b);
    } else {
        ensuref(logRatio < LOG_LIMIT,
                "product(a) / product(b) exceeds 10^18");
    }

    inf.readEof();
}
