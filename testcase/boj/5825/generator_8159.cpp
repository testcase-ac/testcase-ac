#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of barns: small for hand verification
    int N = rnd.next(2, 12);

    // Choose tree shape hyper-parameter
    int treeType = rnd.next(0, 3);
    vector<tuple<int,int>> edges;
    edges.reserve(N-1);

    if (treeType == 0) {
        // Path
        for (int i = 2; i <= N; ++i)
            edges.emplace_back(i-1, i);
    } else if (treeType == 1) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; ++i)
            if (i != center)
                edges.emplace_back(center, i);
    } else if (treeType == 2) {
        // Random parent tree
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    } else {
        // Comb-like: small backbone with leaves
        int backbone = max(2, N/2);
        if (backbone > N) backbone = N;
        // backbone path
        for (int i = 2; i <= backbone; ++i)
            edges.emplace_back(i-1, i);
        // attach remaining as leaves
        for (int i = backbone+1; i <= N; ++i) {
            int attach = rnd.next(1, backbone);
            edges.emplace_back(attach, i);
        }
    }

    // Hyper-parameter for color bias
    int pType = rnd.next(0, 2);
    double p;
    if (pType == 0) {
        // mostly white
        p = rnd.next(0.0, 0.3);
    } else if (pType == 1) {
        // balanced
        p = rnd.next(0.4, 0.6);
    } else {
        // mostly black
        p = rnd.next(0.7, 1.0);
    }

    // Shuffle edge order for variability
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges) {
        int a, b;
        tie(a, b) = e;
        int t = (rnd.next() < p ? 1 : 0);
        println(a, b, t);
    }
    return 0;
}
