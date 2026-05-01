#include "testlib.h"
using namespace std;

struct Edge {
    int u, v, w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0;
    vector<char> gender; // 1-based
    vector<Edge> edges;

    auto addEdge = [&](int u, int v, int w) {
        edges.push_back({u, v, w});
    };

    auto buildBipartiteTreeWithExtras = [&](int extraProb, int invalidProb, int maxEdges, int maxW) {
        edges.clear();
        vector<vector<bool>> exist(N + 1, vector<bool>(N + 1, false));

        vector<int> Mnodes, Wnodes;
        for (int i = 1; i <= N; ++i) {
            if (gender[i] == 'M') Mnodes.push_back(i);
            else Wnodes.push_back(i);
        }

        // assume both non-empty
        int m0 = rnd.any(Mnodes);
        int w0 = rnd.any(Wnodes);
        int w = rnd.next(1, maxW);
        addEdge(m0, w0, w);
        exist[m0][w0] = exist[w0][m0] = true;

        vector<int> MsIn, WsIn;
        MsIn.push_back(m0);
        WsIn.push_back(w0);

        vector<int> remaining;
        remaining.reserve(N - 2);
        for (int i = 1; i <= N; ++i) {
            if (i != m0 && i != w0) remaining.push_back(i);
        }
        shuffle(remaining.begin(), remaining.end());

        for (int u : remaining) {
            int v;
            if (gender[u] == 'M') {
                v = rnd.any(WsIn);
                MsIn.push_back(u);
            } else {
                v = rnd.any(MsIn);
                WsIn.push_back(u);
            }
            int ww = rnd.next(1, maxW);
            addEdge(u, v, ww);
            exist[u][v] = exist[v][u] = true;
        }

        for (int i = 1; i <= N; ++i) {
            if ((int)edges.size() >= maxEdges) break;
            for (int j = i + 1; j <= N; ++j) {
                if ((int)edges.size() >= maxEdges) break;
                if (exist[i][j]) continue;
                if (gender[i] != gender[j]) {
                    if (rnd.next(0, 99) < extraProb) {
                        int ww = rnd.next(1, maxW);
                        addEdge(i, j, ww);
                        exist[i][j] = exist[j][i] = true;
                    }
                } else {
                    if (rnd.next(0, 99) < invalidProb) {
                        int ww = rnd.next(1, maxW);
                        addEdge(i, j, ww);
                        exist[i][j] = exist[j][i] = true;
                    }
                }
            }
        }
    };

    int mode = rnd.next(0, 6);

    if (mode == 0) {
        // All same gender, impossible after filtering
        N = rnd.next(2, 4);
        gender.assign(N + 1, 'M');
        char c = (rnd.next(0, 1) == 0 ? 'M' : 'W');
        for (int i = 1; i <= N; ++i) gender[i] = c;
        edges.clear();
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                addEdge(i, j, rnd.next(1, 20));
    } else if (mode == 1) {
        // N=2 small, always possible
        N = 2;
        gender.assign(N + 1, 'M');
        if (rnd.next(0, 1) == 0) {
            gender[1] = 'M'; gender[2] = 'W';
        } else {
            gender[1] = 'W'; gender[2] = 'M';
        }
        edges.clear();
        int k = rnd.next(1, 3);
        for (int i = 0; i < k; ++i)
            addEdge(1, 2, rnd.next(1, 20));
    } else if (mode == 2) {
        // Small connected bipartite graph with extras
        N = rnd.next(4, 7);
        gender.assign(N + 1, 'M');
        int mCount = rnd.next(1, N - 1); // ensure both genders
        for (int i = 1; i <= N; ++i)
            gender[i] = (i <= mCount ? 'M' : 'W');
        buildBipartiteTreeWithExtras(40, 60, 30, 20);
    } else if (mode == 3) {
        // Underlying graph connected, but some nodes have no valid edges
        N = 4;
        gender.assign(N + 1, 'M');
        gender[1] = 'M';
        gender[2] = 'M';
        gender[3] = 'W';
        gender[4] = 'W';
        edges.clear();
        addEdge(1, 2, rnd.next(1, 10)); // M-M invalid
        addEdge(2, 3, rnd.next(1, 10)); // M-W valid
        addEdge(3, 4, rnd.next(1, 10)); // W-W invalid
    } else if (mode == 4) {
        // Medium size, denser bipartite graph with extras
        N = rnd.next(8, 12);
        gender.assign(N + 1, 'M');
        int mCount = rnd.next(1, N - 1);
        for (int i = 1; i <= N; ++i)
            gender[i] = (i <= mCount ? 'M' : 'W');
        int extraProb = rnd.next(60, 90);
        int invalidProb = rnd.next(30, 60);
        buildBipartiteTreeWithExtras(extraProb, invalidProb, 30, 30);
    } else if (mode == 5) {
        // Cheaper invalid edges tempt wrong MST ignoring constraints
        N = 4;
        gender.assign(N + 1, 'M');
        gender[1] = 'M';
        gender[2] = 'M';
        gender[3] = 'W';
        gender[4] = 'W';
        edges.clear();
        int base = 10;
        addEdge(1, 3, base + rnd.next(0, 5));
        addEdge(1, 4, base + rnd.next(0, 5));
        addEdge(2, 3, base + rnd.next(0, 5));
        // very cheap invalid edges
        addEdge(1, 2, 1);
        addEdge(3, 4, 1);
    } else {
        // mode == 6
        // Cross-edge forest (disconnected), but whole graph connected via invalid edges
        N = 5;
        gender.assign(N + 1, 'M');
        gender[1] = 'M';
        gender[2] = 'W';
        gender[3] = 'M';
        gender[4] = 'W';
        gender[5] = 'M';
        edges.clear();
        int w1 = rnd.next(4, 8);
        int w2 = rnd.next(4, 8);
        int w3 = rnd.next(4, 8);
        // cross edges (two components)
        addEdge(1, 2, w1);
        addEdge(2, 3, w2);
        addEdge(4, 5, w3);
        // same-gender edges that connect components if constraints ignored
        addEdge(3, 5, 1);              // M-M very cheap
        addEdge(1, 3, rnd.next(2, 5)); // M-M
        addEdge(2, 4, rnd.next(2, 5)); // W-W
    }

    int M = (int)edges.size();

    println(N, M);

    // genders (1-based)
    for (int i = 1; i <= N; ++i) {
        if (i > 1) printf(" ");
        printf("%c", gender[i]);
    }
    printf("\n");

    for (const auto &e : edges) {
        println(e.u, e.v, e.w);
    }

    return 0;
}
