#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int treeMode = rnd.next(1, 5);
    int lenMode = rnd.next(1, 3);

    int N;
    if (treeMode == 1) {
        N = rnd.next(3, 8);      // small line
    } else if (treeMode == 2) {
        N = rnd.next(5, 12);     // star-ish
    } else if (treeMode == 3) {
        N = rnd.next(6, 15);     // random tree
    } else if (treeMode == 4) {
        N = rnd.next(6, 15);     // long path + branches
    } else { // treeMode == 5
        N = rnd.next(7, 15);     // binary-like
    }

    auto randDist = [&](int mode) -> int {
        if (mode == 1) {
            return rnd.next(1, 5);
        } else if (mode == 2) {
            int t = rnd.next(1, 2);
            if (t == 1) return rnd.next(1, 5);
            else return rnd.next(6, 100);
        } else {
            int t = rnd.next(1, 3);
            if (t == 1) return rnd.next(1, 5);
            else if (t == 2) return rnd.next(6, 100);
            else return rnd.next(500, 10000);
        }
    };

    vector<int> parent(N + 1);
    vector<int> distEdge(N + 1);
    parent[1] = 0;

    // Build tree with parent[i] < i
    if (treeMode == 1) {
        // Line: 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            parent[i] = i - 1;
            distEdge[i] = randDist(lenMode);
        }
    } else if (treeMode == 2) {
        // Star centered at 1
        for (int i = 2; i <= N; i++) {
            parent[i] = 1;
            distEdge[i] = randDist(lenMode);
        }
    } else if (treeMode == 3) {
        // Random tree: each node connects to random earlier node
        for (int i = 2; i <= N; i++) {
            parent[i] = rnd.next(1, i - 1);
            distEdge[i] = randDist(lenMode);
        }
    } else if (treeMode == 4) {
        // Long path + branches near the end of the path
        int pathLen = rnd.next(2, N - 1); // ensure at least one branch node
        for (int i = 2; i <= pathLen; i++) {
            parent[i] = i - 1;
            distEdge[i] = randDist(lenMode);
        }
        for (int i = pathLen + 1; i <= N; i++) {
            int lo = pathLen - 2;
            if (lo < 2) lo = 2;
            int hi = pathLen;
            if (lo > hi) lo = hi; // safety, though shouldn't trigger
            parent[i] = rnd.next(lo, hi);
            distEdge[i] = randDist(lenMode);
        }
    } else {
        // Binary-like tree: parent[i] = i/2
        for (int i = 2; i <= N; i++) {
            parent[i] = i / 2;
            distEdge[i] = randDist(lenMode);
        }
    }

    // Compute depths
    vector<int> depth(N + 1);
    depth[1] = 0;
    int maxDepth = 0;
    for (int i = 2; i <= N; i++) {
        depth[i] = depth[parent[i]] + 1;
        if (depth[i] > maxDepth) maxDepth = depth[i];
    }

    // Messenger parameters
    int messengerMode = rnd.next(1, 5);
    vector<long long> S(N + 1), V(N + 1);

    if (messengerMode == 1) {
        // Balanced random small values
        for (int i = 2; i <= N; i++) {
            S[i] = rnd.next(0, 50);
            V[i] = rnd.next(1, 20);
        }
    } else if (messengerMode == 2) {
        // Uniform speed, varied start times (including large)
        long long baseV = rnd.next(1, 15);
        for (int i = 2; i <= N; i++) {
            V[i] = baseV;
            int t = rnd.next(1, 3);
            if (t == 1) {
                S[i] = rnd.next(0, 20);
            } else if (t == 2) {
                S[i] = rnd.next(50, 500);
            } else {
                S[i] = rnd.next(1000, 1000000);
            }
        }
    } else if (messengerMode == 3) {
        // Extreme tradeoffs: very late but fast vs early but slow
        for (int i = 2; i <= N; i++) {
            int t = rnd.next(0, 1);
            if (t == 0) {
                // Late but "fast-ish"
                S[i] = rnd.next(1000, 1000000000);
                V[i] = rnd.next(1, 5);
            } else {
                // Early but slow
                S[i] = rnd.next(0, 5);
                V[i] = rnd.next(100, 100000);
            }
        }
    } else if (messengerMode == 4) {
        // Depth-based patterns (monotone relationships)
        int subMode = rnd.next(1, 2);
        long long baseS = rnd.next(0, 10);
        long long incS = rnd.next(1, 10);
        long long baseV = rnd.next(1, 5);
        long long incV = rnd.next(1, 5);
        if (subMode == 1) {
            // Deeper: later start, slower speed (bad combination)
            for (int i = 2; i <= N; i++) {
                S[i] = baseS + incS * depth[i];
                V[i] = baseV + incV * (maxDepth - depth[i]);
            }
        } else {
            // Deeper: earlier start, faster speed (good combination)
            for (int i = 2; i <= N; i++) {
                S[i] = baseS + incS * (maxDepth - depth[i]);
                V[i] = baseV + incV * depth[i];
            }
        }
    } else {
        // Same start time for all, varied speeds
        long long baseS = rnd.next(0, 20);
        for (int i = 2; i <= N; i++) {
            S[i] = baseS;
            int t = rnd.next(1, 3);
            if (t == 1) {
                V[i] = rnd.next(1, 5);
            } else if (t == 2) {
                V[i] = rnd.next(6, 20);
            } else {
                V[i] = rnd.next(50, 1000);
            }
        }
    }

    // Output
    println(N);

    // Shuffle edge order for variety
    vector<int> edgeOrder;
    for (int i = 2; i <= N; i++) edgeOrder.push_back(i);
    shuffle(edgeOrder.begin(), edgeOrder.end());

    for (int idx : edgeOrder) {
        println(parent[idx], idx, distEdge[idx]);
    }

    // Messengers: for cities 2..N in order
    for (int i = 2; i <= N; i++) {
        println(S[i], V[i]);
    }

    return 0;
}
