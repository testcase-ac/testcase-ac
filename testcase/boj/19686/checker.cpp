#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int n, m;
vector<tuple<int, int, int>> queries;

vector<int> readAnswer(InStream& stream) {
    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        x[i] = stream.readInt(1, 1000000000, format("X_%d", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after reconstructed array");
    }

    for (int i = 0; i < m; ++i) {
        auto [a, b, c] = queries[i];
        int got = min(x[a], x[b]);
        if (got != c) {
            stream.quitf(_wa,
                         "query %d requires min(X_%d, X_%d) = %d, got %d",
                         i + 1,
                         a,
                         b,
                         c,
                         got);
        }
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    queries.reserve(m);

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        int c = inf.readInt();
        queries.emplace_back(a, b, c);
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid reconstructed array");
}
