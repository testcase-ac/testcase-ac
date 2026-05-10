#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of cards
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Card colors: N tokens, each R/G/B
    vector<char> card(N + 1);
    for (int i = 1; i <= N; ++i) {
        string c = inf.readToken("[RGB]", "card_color");
        ensuref(c.size() == 1, "Card color token must be single character");
        card[i] = c[0];
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // M: number of villages, K: number of roads
    int M = inf.readInt(1, 500, "M");
    inf.readSpace();
    int K = inf.readInt(0, 10000, "K");
    inf.readEoln();

    // Read edges, check:
    // - 1 <= a, b <= M
    // - a != b (no loops)
    // - no multiple edges between same unordered pair
    // - color is R/G/B
    set<pair<int,int>> edges;
    vector<vector<pair<int,char>>> g(M + 1);

    for (int i = 0; i < K; ++i) {
        int a = inf.readInt(1, M, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, M, "b_i");
        inf.readSpace();
        string c = inf.readToken("[RGB]", "edge_color");
        inf.readEoln();

        ensuref(a != b, "Loop detected at edge index %d: (%d, %d)", i, a, b);
        if (a > b) swap(a, b);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({a, b});

        char col = c[0];
        g[a].push_back({b, col});
        g[b].push_back({a, col});
    }

    // Implied by statement: "항상 1번 마을로부터 시작하여 ... 이동해 가는데"
    // So village 1 must exist, and presumably the graph may be disconnected.
    // No explicit global property like "graph is connected", so we do not enforce connectivity.

    // End of file
    inf.readEof();
}
