#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Hyper-parameter for number of computers/people
    int N = rnd.next(2, 10);
    // Number of games between 2 and N
    int M = rnd.next(2, N);
    
    // Ensure each game has at least one buyer
    vector<int> sizes(M, 1);
    int rem = N - M;
    for (int i = 0; i < rem; ++i) {
        int gi = rnd.next(0, M - 1);
        sizes[gi]++;
    }
    
    // Assign games to people and shuffle
    vector<int> games;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < sizes[i]; ++j)
            games.push_back(i + 1);
    }
    shuffle(games.begin(), games.end());
    
    // Group members by game
    vector<vector<int>> members(M + 1);
    for (int i = 0; i < N; ++i) {
        members[games[i]].push_back(i + 1);
    }
    
    // Compute maximum unique pairs
    long long maxUnique = 1LL * N * (N - 1) / 2;
    int Qmax = min<long long>(20, maxUnique + 10);
    // Hyper-parameter for Q distribution bias: -1 => small, 0 => uniform, 1 => large
    int bias = rnd.next(-1, 1);
    int Q = rnd.wnext(Qmax, bias) + 1; // ensure Q in [1, Qmax]
    
    // Probabilities for edge types
    double p_intra = rnd.next(0.0, 1.0);
    double p_inter = rnd.next(0.0, 1.0);
    
    // Generate cables (edges)
    vector<pair<int,int>> edges;
    edges.reserve(Q);
    for (int i = 0; i < Q; ++i) {
        if (rnd.next() < p_intra) {
            // Try to connect within a same-game group
            int g = rnd.next(1, M);
            if (members[g].size() >= 2) {
                int a = rnd.any(members[g]);
                int b = rnd.any(members[g]);
                edges.emplace_back(a, b);
                continue;
            }
        }
        if (rnd.next() < p_inter && M >= 2) {
            // Connect between two different groups
            int g1 = rnd.next(1, M), g2 = rnd.next(1, M);
            if (g1 == g2) {
                g2 = (g1 % M) + 1;
            }
            int a = rnd.any(members[g1]);
            int b = rnd.any(members[g2]);
            edges.emplace_back(a, b);
            continue;
        }
        // Otherwise random endpoints (self-loops and duplicates allowed)
        int a = rnd.next(1, N);
        int b = rnd.next(1, N);
        edges.emplace_back(a, b);
    }
    
    // Output in required format
    println(N, M, Q);
    println(games);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
