#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        string c = inf.readToken("[OE]{1,100000}", "c");
        inf.readEoln();

        ensuref((int)c.size() == N,
                "case %d has c length %d, expected %d",
                tc,
                (int)c.size(),
                N);

        sumN += N;
        ensuref(sumN <= 100000,
                "sum of N exceeds 100000 at case %d: %lld",
                tc,
                sumN);
    }

    inf.readEof();
    return 0;
}
