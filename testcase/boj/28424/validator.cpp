#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXQ = 100000;
    const long long MAXM = 1000000000LL;
    const long long MAXX = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    vector<long long> m(N + 1);
    for (int i = 1; i <= N; ++i) {
        m[i] = inf.readLong(1LL, MAXM, "m_i");
        inf.readEoln();
    }

    for (int qi = 0; qi < Q; ++qi) {
        int t = inf.readInt(1, 2, "t");
        if (t == 1) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            long long x = inf.readLong(1LL, MAXX, "x");
            inf.readEoln();
        } else { // t == 2
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
