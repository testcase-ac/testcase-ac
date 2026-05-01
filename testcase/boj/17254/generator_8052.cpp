#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of keyboards
    int N = rnd.next(1, 10);
    // Generate M with three size regimes for variability
    int branch = rnd.next(0, 2);
    int M;
    if (branch == 0) {
        // small: at most one press per keyboard
        M = rnd.next(1, max(1, N));
    } else if (branch == 1) {
        // medium: between N+1 and up to min(50, 5*N)
        int lo = N + 1;
        int hi = max(N + 1, min(50, N * 5));
        M = rnd.next(lo, hi);
    } else {
        // possibly larger: up to min(100, 10*N)
        int lo = 1;
        int hi = min(100, N * 10);
        M = rnd.next(lo, hi);
    }
    M = min(M, 1000);

    // Prepare to generate presses: enforce unique times per keyboard
    vector<tuple<int,int,char>> presses;
    vector<set<int>> used(N+1);
    // weight parameter for time distribution
    int wt = rnd.next(-2, 2);
    string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < M; i++) {
        int a = rnd.next(1, N);
        int b;
        int attempts = 0;
        do {
            b = rnd.wnext(1001, wt);  // times in [0,1000]
            attempts++;
        } while (used[a].count(b) && attempts < 1000);
        if (used[a].count(b)) {
            // fallback to any unused time
            for (int x = 0; x <= 1000; x++) {
                if (!used[a].count(x)) {
                    b = x;
                    break;
                }
            }
        }
        used[a].insert(b);
        char c = rnd.any(alph);
        presses.emplace_back(a, b, c);
    }

    // Shuffle input order to test sorting logic
    shuffle(presses.begin(), presses.end());

    // Output
    println(N, M);
    for (auto &t : presses) {
        int a, b;
        char c;
        tie(a, b, c) = t;
        println(a, b, c);
    }

    return 0;
}
