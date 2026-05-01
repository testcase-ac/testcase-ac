#include "testlib.h"
using namespace std;

struct Edge {
    int u, v, w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (number of cities), small but varied
    int Nmode = rnd.next(0, 3);
    int N;
    if (Nmode == 0) N = 2;
    else if (Nmode == 1) N = rnd.next(3, 5);
    else if (Nmode == 2) N = rnd.next(6, 8);
    else N = rnd.next(9, 10);

    // Choose Q (number of queries), small to keep input compact
    int Qmax = 7;
    int Q = rnd.next(1, min(Qmax, N + 2));

    // Weight pattern for edges
    int wtype = rnd.next(0, 2); // 0: all ones, 1: small random, 2: wide random
    auto getW = [&]() -> int {
        if (wtype == 0) return 1;
        if (wtype == 1) return rnd.next(1, 20);
        // wide range
        return rnd.next(1, 100000000);
    };

    // Generate tree
    vector<Edge> edges;
    edges.reserve(N - 1);
    int treeType = rnd.next(0, 3); // 0: path, 1: star, 2: random, 3: binary-like

    if (treeType == 0) {
        // Path: 0-1-2-...-(N-1)
        for (int i = 1; i < N; ++i) {
            edges.push_back({i - 1, i, getW()});
        }
    } else if (treeType == 1) {
        // Star centered at 0
        for (int i = 1; i < N; ++i) {
            edges.push_back({0, i, getW()});
        }
    } else if (treeType == 2) {
        // Random tree: each node connects to a random previous node
        for (int i = 1; i < N; ++i) {
            int p = rnd.next(0, i - 1);
            edges.push_back({p, i, getW()});
        }
    } else {
        // Binary-like tree: parent(i) = (i-1)/2
        for (int i = 1; i < N; ++i) {
            int p = (i - 1) / 2;
            edges.push_back({p, i, getW()});
        }
    }

    // Optionally shuffle edge order
    if (rnd.next(0, 1)) {
        shuffle(edges.begin(), edges.end());
    }

    // Output N, Q
    println(N, Q);

    // Output edges
    for (const auto &e : edges) {
        println(e.u, e.v, e.w);
    }

    // Helper to generate a random query (except the first special ones)
    auto genRandomQuery = [&](int N) {
        int S, T;
        vector<int> X, Y;

        if (N == 2) {
            // Only possible split is {0} vs {1}
            int flip = rnd.next(0, 1);
            S = 1;
            T = 1;
            if (flip == 0) {
                X.push_back(0);
                Y.push_back(1);
            } else {
                X.push_back(1);
                Y.push_back(0);
            }
        } else {
            // Choose total number of distinct cities in this query
            int K;
            if (N <= 3) {
                K = rnd.next(2, N);
            } else {
                int pattern = rnd.next(0, 2);
                if (pattern == 0) {
                    K = 2; // both sets size 1
                } else if (pattern == 1) {
                    K = rnd.next(2, min(4, N)); // small
                } else {
                    int low = max(2, N - 2);    // large, near N
                    K = rnd.next(low, N);
                }
            }

            // Split K into S and T
            int splitType = rnd.next(0, 2);
            if (splitType == 0) {
                S = 1;
                T = K - 1;
            } else if (splitType == 1) {
                S = K - 1;
                T = 1;
            } else {
                S = rnd.next(1, K - 1);
                T = K - S;
            }

            // Pick K distinct cities
            vector<int> nodes;
            nodes.reserve(N);
            for (int i = 0; i < N; ++i) nodes.push_back(i);
            shuffle(nodes.begin(), nodes.end());

            X.assign(nodes.begin(), nodes.begin() + S);
            Y.assign(nodes.begin() + S, nodes.begin() + S + T);
        }

        println(S, T);
        println(X);
        println(Y);
    };

    // Generate queries
    for (int j = 0; j < Q; ++j) {
        if (j == 0) {
            // Special simple query: single factory in city 0 and N-1
            int S = 1, T = 1;
            vector<int> X(1), Y(1);
            X[0] = 0;
            Y[0] = N - 1;
            println(S, T);
            println(X);
            println(Y);
        } else if (j == 1 && Q >= 2) {
            // Second query: one side very small, other side large
            int S = 1;
            vector<int> X(1);
            X[0] = 0;

            vector<int> Y;
            Y.reserve(N - 1);
            for (int i = 0; i < N; ++i) {
                if (i != 0) Y.push_back(i);
            }
            // Occasionally shuffle the large set for variability
            if (rnd.next(0, 1)) shuffle(Y.begin(), Y.end());
            int T = (int)Y.size();

            println(S, T);
            println(X);
            println(Y);
        } else {
            // Randomly generated query
            genRandomQuery(N);
        }
    }

    return 0;
}
