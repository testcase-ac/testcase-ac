#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_N = 10000000000000LL;
    const int MAX_T = 1000;
    const int MIN_P = -100000;
    const int MAX_P = 100000;

    int t = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(1LL, MAX_N, "N");
        inf.readSpace();
        long long a = inf.readLong(0LL, n, "A");
        inf.readSpace();
        long long b = inf.readLong(0LL, n, "B");
        inf.readSpace();
        long long c = inf.readLong(0LL, n, "C");
        inf.readSpace();
        long long d = inf.readLong(0LL, n, "D");
        inf.readSpace();
        long long e = inf.readLong(0LL, n, "E");
        inf.readSpace();
        long long f = inf.readLong(0LL, n, "F");
        inf.readEoln();

        ensuref(a + b + c == n, "A+B+C must equal N");
        ensuref(d + e + f == n, "D+E+F must equal N");

        for (int i = 1; i <= 3; ++i) {
            inf.readInt(MIN_P, MAX_P, format("P_%d4", i).c_str());
            inf.readSpace();
            inf.readInt(MIN_P, MAX_P, format("P_%d5", i).c_str());
            inf.readSpace();
            inf.readInt(MIN_P, MAX_P, format("P_%d6", i).c_str());
            inf.readEoln();
        }
    }

    inf.readEof();
}
