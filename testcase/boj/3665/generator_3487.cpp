#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(2, 10);
        // last year's ranking: a random permutation of 1..n
        vector<int> orig(n);
        iota(orig.begin(), orig.end(), 1);
        shuffle(orig.begin(), orig.end());
        bool makeImpossible = (n >= 3 && rnd.next() < 0.3);
        if (makeImpossible) {
            // Produce an impossible case by creating a 3-cycle
            println(n);
            println(orig);
            int x = rnd.next(0, n - 3);
            int y = rnd.next(x + 1, n - 2);
            int z = rnd.next(y + 1, n - 1);
            int u = orig[x], v = orig[y], w = orig[z];
            vector<pair<int,int>> flips;
            flips.emplace_back(min(u, v), max(u, v));
            flips.emplace_back(min(v, w), max(v, w));
            flips.emplace_back(min(u, w), max(u, w));
            println((int)flips.size());
            shuffle(flips.begin(), flips.end());
            for (auto &pr : flips) {
                println(pr.first, pr.second);
            }
        } else {
            // Produce a consistent case with a valid unique ranking
            // by doing some adjacent swaps to orig to get c
            vector<int> c = orig;
            int k = rnd.next(0, n);
            for (int t = 0; t < k; t++) {
                int i = rnd.next(0, n - 2);
                swap(c[i], c[i + 1]);
            }
            // Determine flips needed to turn orig into c
            vector<int> pos_o(n + 1), pos_c(n + 1);
            for (int i = 0; i < n; i++) {
                pos_o[orig[i]] = i;
                pos_c[c[i]] = i;
            }
            vector<pair<int,int>> flips;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int u = orig[i], v = orig[j];
                    // originally u before v; if in c it's reversed, record flip
                    if (pos_c[u] > pos_c[v]) {
                        flips.emplace_back(min(u, v), max(u, v));
                    }
                }
            }
            println(n);
            println(orig);
            println((int)flips.size());
            shuffle(flips.begin(), flips.end());
            for (auto &pr : flips) {
                println(pr.first, pr.second);
            }
        }
    }
    return 0;
}
