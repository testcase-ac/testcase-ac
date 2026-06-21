#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000000, "N");
    inf.readEoln();

    string t = inf.readToken("[a-z]{2,2000000}", "T");
    ensuref((int)t.size() == n, "T length must be N: expected %d, got %d", n, (int)t.size());
    inf.readEoln();

    int m = inf.readInt(1, 26 * 26, "M");
    inf.readEoln();

    set<pair<char, char>> edges;
    for (int i = 0; i < m; ++i) {
        string edge = inf.readToken("[a-z]{2,2}", "edge");
        inf.readEoln();

        auto directedEdge = make_pair(edge[0], edge[1]);
        ensuref(edges.insert(directedEdge).second,
                "duplicate directed edge at index %d: %c%c", i + 1, edge[0], edge[1]);
    }

    inf.readEof();
}
