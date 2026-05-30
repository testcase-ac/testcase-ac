#include "testlib.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 300000, "M");
    inf.readEoln();

    long long planarEdgeLimit = n <= 2 ? n - 1LL : 3LL * n - 6;
    ensuref(m <= planarEdgeLimit,
            "a simple planar graph with N=%d cannot have M=%d edges",
            n, m);

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    Graph graph(n);
    set<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i + 1, u, v);
        pair<int, int> edge = {min(u, v), max(u, v)};
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: %d %d", i + 1, u, v);
        boost::add_edge(u - 1, v - 1, graph);
    }

    ensuref(boost::boyer_myrvold_planarity_test(graph), "graph must be planar");
    inf.readEof();
}
