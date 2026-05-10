#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    // Total number of hexagons
    long long total = 1LL * N * (N + 1) / 2;

    // Read N lines, i-th line has i characters, each 'R' or 'B'
    long long cnt = 0;
    for (int i = 1; i <= N; ++i) {
        string s = inf.readLine("[RB]{"+to_string(i)+"}", "row");
        ensuref((int)s.size() == i, "Line %d must have exactly %d characters, got %d", i, i, (int)s.size());
        cnt += i;
    }
    ensuref(cnt == total, "Total number of hexagons is %lld, expected %lld", cnt, total);

    inf.readEof();
}
