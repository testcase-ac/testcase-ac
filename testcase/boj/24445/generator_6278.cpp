#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

static vector<pair<int,int>> allPairs(const vector<int>& nodes) {
    vector<pair<int,int>> res;
    for (int i = 0; i < (int)nodes.size(); i++)
        for (int j = i + 1; j < (int)nodes.size(); j++)
            res.emplace_back(min(nodes[i], nodes[j]), max(nodes[i], nodes[j]));
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(5, 12);
    // Type of graph to generate
    int type = rnd.next(0, 4);

    // Prepare all possible edges
    vector<pair<int,int>> allps;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            allps.emplace_back(i, j);
    shuffle(allps.begin(), allps.end());

    vector<pair<int,int>> edges;
    vector<int> A, B; // for disconnected

    if (type == 0) {
        // Sparse-ish random graph
        int total = allps.size();
        int lo = N - 1;
        int hi = min(total, N - 1 + N);
        int M = rnd.next(lo, hi);
        edges.assign(allps.begin(), allps.begin() + M);
    }
    else if (type == 1) {
        // Dense-ish random graph
        int total = allps.size();
        int lo = max(N, total / 2);
        int hi = total;
        int M = rnd.next(lo, hi);
        edges.assign(allps.begin(), allps.begin() + M);
    }
    else if (type == 2) {
        // Chain + up to 2 extra edges
        // Build chain
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i+1);
            used[i][i+1] = used[i+1][i] = true;
        }
        // Extras
        vector<pair<int,int>> rem;
        for (auto &p : allps)
            if (!used[p.first][p.second])
                rem.push_back(p);
        shuffle(rem.begin(), rem.end());
        int extra = rnd.next(0, min((int)rem.size(), 2));
        for (int i = 0; i < extra; i++)
            edges.push_back(rem[i]);
    }
    else if (type == 3) {
        // Star + up to 2 extra edges
        int center = rnd.next(1, N);
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        for (int i = 1; i <= N; i++) if (i != center) {
            int u = min(i, center), v = max(i, center);
            edges.emplace_back(u, v);
            used[u][v] = used[v][u] = true;
        }
        vector<pair<int,int>> rem;
        for (auto &p : allps)
            if (!used[p.first][p.second])
                rem.push_back(p);
        shuffle(rem.begin(), rem.end());
        int extra = rnd.next(0, min((int)rem.size(), 2));
        for (int i = 0; i < extra; i++)
            edges.push_back(rem[i]);
    }
    else {
        // Disconnected: two components A and B
        vector<int> nodes(N);
        for (int i = 0; i < N; i++) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int k = rnd.next(1, N - 1);
        A = vector<int>(nodes.begin(), nodes.begin() + k);
        B = vector<int>(nodes.begin() + k, nodes.end());

        // Build component A
        if ((int)A.size() >= 2) {
            shuffle(A.begin(), A.end());
            // spanning tree in A
            vector<vector<bool>> usedA(N+1, vector<bool>(N+1, false));
            for (int i = 1; i < (int)A.size(); i++) {
                int u = min(A[0], A[i]), v = max(A[0], A[i]);
                edges.emplace_back(u, v);
                usedA[u][v] = usedA[v][u] = true;
            }
            // extras in A
            auto pairsA = allPairs(A);
            vector<pair<int,int>> remA;
            for (auto &p : pairsA)
                if (!usedA[p.first][p.second])
                    remA.push_back(p);
            shuffle(remA.begin(), remA.end());
            int extraA = rnd.next(0, min((int)remA.size(), (int)A.size()-1));
            for (int i = 0; i < extraA; i++)
                edges.push_back(remA[i]);
        }
        // Build component B
        if ((int)B.size() >= 2) {
            shuffle(B.begin(), B.end());
            vector<vector<bool>> usedB(N+1, vector<bool>(N+1, false));
            for (int i = 1; i < (int)B.size(); i++) {
                int u = min(B[0], B[i]), v = max(B[0], B[i]);
                edges.emplace_back(u, v);
                usedB[u][v] = usedB[v][u] = true;
            }
            auto pairsB = allPairs(B);
            vector<pair<int,int>> remB;
            for (auto &p : pairsB)
                if (!usedB[p.first][p.second])
                    remB.push_back(p);
            shuffle(remB.begin(), remB.end());
            int extraB = rnd.next(0, min((int)remB.size(), (int)B.size()-1));
            for (int i = 0; i < extraB; i++)
                edges.push_back(remB[i]);
        }
    }

    // Final shuffle and choose start
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    int R;
    if (type == 4) {
        // pick R from one component to ensure the other is unreachable
        if (rnd.next(0,1) == 0 && !A.empty()) R = rnd.any(A);
        else R = rnd.any(B);
    } else {
        R = rnd.next(1, N);
    }

    // Output
    println(N, M, R);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
