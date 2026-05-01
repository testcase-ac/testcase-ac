#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a pattern for DAG structure
    int pattern = rnd.next(0, 5);
    int N;
    vector<int> perm;
    vector<pair<int,int>> edges;

    switch (pattern) {
        case 0: { // simple chain
            N = rnd.next(2, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            for (int i = 1; i < N; i++) {
                edges.emplace_back(perm[i-1], perm[i]);
            }
            break;
        }
        case 1: { // random spanning tree (connected DAG)
            N = rnd.next(3, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            for (int i = 1; i < N; i++) {
                int p = rnd.next(0, i-1);
                edges.emplace_back(perm[p], perm[i]);
            }
            break;
        }
        case 2: { // sparse random DAG
            N = rnd.next(4, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            int maxE = N*(N-1)/2;
            int maxSparse = max(maxE/3, N-1);
            int M = rnd.next(N-1, maxSparse);
            vector<pair<int,int>> cand;
            for (int i = 0; i < N; i++)
                for (int j = i+1; j < N; j++)
                    cand.emplace_back(perm[i], perm[j]);
            shuffle(cand.begin(), cand.end());
            edges.insert(edges.end(), cand.begin(), cand.begin() + M);
            break;
        }
        case 3: { // dense random DAG
            N = rnd.next(4, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            int maxE = N*(N-1)/2;
            int minDense = max(1, maxE - (N-1));
            int M = rnd.next(minDense, maxE);
            vector<pair<int,int>> cand;
            for (int i = 0; i < N; i++)
                for (int j = i+1; j < N; j++)
                    cand.emplace_back(perm[i], perm[j]);
            shuffle(cand.begin(), cand.end());
            edges.insert(edges.end(), cand.begin(), cand.begin() + M);
            break;
        }
        case 4: { // bipartite complete DAG
            N = rnd.next(5, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            int r = rnd.next(1, N-1);
            for (int i = 0; i < r; i++)
                for (int j = r; j < N; j++)
                    edges.emplace_back(perm[i], perm[j]);
            break;
        }
        case 5: { // star-shaped DAG
            N = rnd.next(3, 12);
            perm.resize(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            int center = rnd.next(0, N-1);
            for (int i = 0; i < N; i++) {
                if (i == center) continue;
                // half of the time reverse direction to add variety
                if (rnd.next(0,1) == 0)
                    edges.emplace_back(perm[center], perm[i]);
                else
                    edges.emplace_back(perm[i], perm[center]);
            }
            break;
        }
    }

    // Finalize
    int M = edges.size();
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
