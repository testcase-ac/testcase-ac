#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 1000000000, "N");
    inf.readEoln();

    int M = inf.readInt(2, 500000, "M");
    inf.readEoln();

    set<pair<int, int>> routes;
    for (int i = 1; i <= M; ++i) {
        int a = inf.readInt(0, N - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N - 1, "b");
        inf.readEoln();

        ensuref(a != b, "route %d has identical endpoints: %d", i, a);
        ensuref(routes.insert({a, b}).second,
                "duplicate route at index %d: [%d, %d]", i, a, b);

        long long clockwiseEdges = (static_cast<long long>(b) - a + N) % N;
        ensuref(clockwiseEdges != static_cast<long long>(N) - 1,
                "route %d covers every stop: [%d, %d]", i, a, b);
    }

    inf.readEof();
    return 0;
}
