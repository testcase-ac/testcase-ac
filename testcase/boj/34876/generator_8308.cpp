#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of production villages
    int N = rnd.next(2, 12);

    // Carrying capacity K: small, medium, or large
    int K;
    int modeK = rnd.next(0, 2);
    if (modeK == 0) K = rnd.next(1, 5);
    else if (modeK == 1) K = rnd.next(6, 49);
    else K = rnd.next(50, 100);

    // Rice sacks at each village: skewed distribution
    vector<int> s(N);
    int t_s = rnd.next(-2, 2);
    for (int i = 0; i < N; i++) {
        s[i] = rnd.wnext(101, t_s); // yields [0,100]
    }

    // Build a tree on nodes 0..N with one of four shapes
    vector<pair<int,int>> edges;
    int treeType = rnd.next(1, 4);
    if (treeType == 1) {
        // Chain: 0-1-2-...-N
        for (int i = 1; i <= N; i++) edges.emplace_back(i-1, i);
    } else if (treeType == 2) {
        // Star centered at 0
        for (int i = 1; i <= N; i++) edges.emplace_back(0, i);
    } else if (treeType == 3) {
        // Balanced-like: parent = i/2
        for (int i = 1; i <= N; i++) edges.emplace_back(i/2, i);
    } else {
        // Random parent
        for (int i = 1; i <= N; i++) edges.emplace_back(rnd.next(0, i-1), i);
    }

    // Edge weights: either small [1,10] or larger [10,100]
    int wMode = rnd.next(0, 1);
    int lo = (wMode == 0 ? 1 : 10);
    int hi = (wMode == 0 ? 10 : 100);
    vector<tuple<int,int,int>> e2;
    for (auto &p : edges) {
        int T = rnd.next(lo, hi);
        e2.emplace_back(p.first, p.second, T);
    }
    // Shuffle edge order to avoid any bias
    shuffle(e2.begin(), e2.end());

    // Output
    println(N, K);
    println(s);
    for (auto &e : e2) {
        int A, B, T;
        tie(A, B, T) = e;
        println(A, B, T);
    }

    return 0;
}
