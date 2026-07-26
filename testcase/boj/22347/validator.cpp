#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500000, "T");
    inf.readEoln();

    long long sumA = 0;
    long long sumB = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string a = inf.readToken("[()]{1,500000}", "A");
        inf.readSpace();
        string b = inf.readToken("[()]{1,500000}", "B");
        inf.readSpace();
        inf.readLong(1LL, 1000000000000000000LL, "K");
        inf.readEoln();

        sumA += a.size();
        sumB += b.size();
        ensuref(sumA <= 500000, "sum of |A| exceeds 500000 at test case %d", tc);
        ensuref(sumB <= 500000, "sum of |B| exceeds 500000 at test case %d", tc);
    }

    inf.readEof();
}
