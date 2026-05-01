#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for n: small, medium, large
    int t = rnd.next(0, 2);
    int n;
    if (t == 0)      n = rnd.next(2, 5);
    else if (t == 1) n = rnd.next(6, 8);
    else             n = rnd.next(9, 12);

    // Generate Pokemon costs and bids
    vector<tuple<int,int,int>> pok(n);
    for (int i = 0; i < n; i++) {
        // c_i in [1,100000], skewed small or large
        int tc = rnd.next(-2, 2);
        int c = rnd.wnext(100000, tc) + 1;
        // a_i, j_i in [1, c], skewed differently
        int ta = rnd.next(-2, 2);
        int tj = rnd.next(-2, 2);
        int a = rnd.wnext(c, ta) + 1;
        int j = rnd.wnext(c, tj) + 1;
        pok[i] = make_tuple(c, a, j);
    }

    // Generate battles: allow duplicates, cap to keep input compact
    int maxPairs = n * (n - 1) / 2;
    int bMax = min(maxPairs, 25);
    int b = rnd.next(1, bMax);

    vector<tuple<int,int,int>> battles;
    battles.reserve(b);
    for (int i = 0; i < b; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) v++;
        int tc = rnd.next(-2, 2);
        int cost = rnd.wnext(100000, tc) + 1;
        battles.emplace_back(u, v, cost);
    }

    // Output
    println(n);
    for (auto &p : pok) {
        int c, a, j;
        tie(c, a, j) = p;
        println(c, a, j);
    }
    println(b);
    for (auto &e : battles) {
        int u, v, cost;
        tie(u, v, cost) = e;
        println(u, v, cost);
    }

    return 0;
}
