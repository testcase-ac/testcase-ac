#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes, keep hand-checkable
    int N = rnd.next(1, 20);

    // Hyper-parameter: choose alphabet upper bound for variability ('a'..maxc)
    int alphaMax = rnd.next(0, 25);
    char maxc = char('a' + alphaMax);

    // Generate labels string
    string s;
    s.reserve(N);
    for (int i = 0; i < N; i++) {
        s.push_back(char(rnd.next('a', maxc)));
    }

    // Choose tree shape: 0=chain, 1=star, 2=random
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 0) {
        // Chain: 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i-1, i);
        }
    } else if (shape == 1) {
        // Star: all nodes connect to 1
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(1, i);
        }
    } else {
        // Random tree: attach each new node to a random existing node
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edges to vary order
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    println(s);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
