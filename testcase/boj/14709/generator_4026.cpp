#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: probability of generating a correct fox sign
    bool isCorrect = rnd.next() < 0.5;

    // The unique correct fox sign edges (thumb=1, middle=3, ring=4)
    vector<pair<int,int>> foxEdges = {{1,3}, {3,4}, {1,4}};
    // Build all possible finger-touch edges among 5 fingers
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= 5; ++i)
        for (int j = i + 1; j <= 5; ++j)
            allEdges.emplace_back(i, j);

    vector<pair<int,int>> edges;
    int N;

    if (isCorrect) {
        // Exactly the 3-clique among {1,3,4}
        N = 3;
        edges = foxEdges;
    } else {
        // Hyper-parameter: bias towards small or large N
        vector<int> tbias = {-2, -1, 0, 1, 2};
        int t = rnd.any(tbias);
        // rnd.wnext(10, t) gives [0..9], so +1 gives N in [1..10]
        N = rnd.wnext(10, t) + 1;

        // Sample N distinct edges
        shuffle(allEdges.begin(), allEdges.end());
        edges.assign(allEdges.begin(), allEdges.begin() + N);

        // Ensure we do not accidentally create the exact fox sign
        if (N == 3) {
            auto tmp = edges;
            sort(tmp.begin(), tmp.end());
            auto fe = foxEdges;
            sort(fe.begin(), fe.end());
            if (tmp == fe) {
                // Replace the first edge with some other
                for (auto &e : allEdges) {
                    if (find(fe.begin(), fe.end(), e) == fe.end()) {
                        edges[0] = e;
                        break;
                    }
                }
            }
        }
    }

    // Randomize edge order and orientation
    double swapP = rnd.next();
    for (auto &e : edges) {
        if (rnd.next() < swapP)
            swap(e.first, e.second);
    }
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
