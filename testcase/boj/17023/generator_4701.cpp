#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of fields
    int N = rnd.next(2, 10);

    // Shortcut time hyper-parameter
    vector<int> Tchoices = {10, 20, 50};
    int Tmax = rnd.any(Tchoices);
    int T = rnd.next(1, Tmax);

    // Cow counts hyper-parameter
    vector<int> Cchoices = {5, 10, 20};
    int maxC = rnd.any(Cchoices);
    vector<int> cows(N);
    for (int i = 0; i < N; i++) {
        cows[i] = rnd.next(0, maxC);
    }

    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    for (int i = 2; i <= N; i++) {
        int j = rnd.next(1, i-1);
        int a = i, b = j;
        if (a > b) swap(a, b);
        edges.emplace_back(a, b);
        used.insert({a, b});
    }

    // All possible edges i<j
    vector<pair<int,int>> all;
    for (int i = 1; i <= N; i++)
        for (int j = i+1; j <= N; j++)
            all.emplace_back(i, j);
    shuffle(all.begin(), all.end());

    // Decide how many extra edges to add, cap total M ≤ 20
    int maxPossible = (int)all.size() - (N-1);
    int capExtra = min({maxPossible, 20 - (N-1), maxPossible});
    if (capExtra < 0) capExtra = 0;
    int extraChoiceRaw = rnd.next(0, maxPossible);
    int extraChoice = min(extraChoiceRaw, capExtra);
    int extra = extraChoice;
    for (auto &p : all) {
        if (extra <= 0) break;
        int a = p.first, b = p.second;
        if (used.count({a, b})) continue;
        edges.emplace_back(a, b);
        used.insert({a, b});
        extra--;
    }

    int M = edges.size();

    // Edge weights hyper-parameter skew
    vector<int> WtParam = {-2, -1, 0, 1, 2};
    int wt_par = rnd.any(WtParam);
    vector<int> w(M);
    for (int i = 0; i < M; i++) {
        if (wt_par == 0) {
            w[i] = rnd.next(1, 25);
        } else {
            w[i] = rnd.wnext(25, wt_par) + 1;
        }
    }

    // Output
    println(N, M, T);
    println(cows);
    for (int i = 0; i < M; i++) {
        println(edges[i].first, edges[i].second, w[i]);
    }
    return 0;
}
