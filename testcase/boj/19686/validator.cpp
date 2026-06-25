#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    vector<int> lower(n + 1, 1);
    vector<tuple<int, int, int>> queries;
    queries.reserve(m);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "C_i");
        inf.readEoln();

        ensuref(a != b, "A_i and B_i must differ at query %d: %d %d", i, a, b);

        lower[a] = max(lower[a], c);
        lower[b] = max(lower[b], c);
        queries.emplace_back(a, b, c);
    }

    for (int i = 0; i < m; ++i) {
        auto [a, b, c] = queries[i];
        ensuref(min(lower[a], lower[b]) == c,
                "no valid array can satisfy query %d: min(X_%d, X_%d) = %d",
                i + 1, a, b, c);
    }

    inf.readEof();
}
