#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of teams
        int n = rnd.next(2, 10);
        // Density parameter for number of games
        double dens = rnd.next();
        // Maximum reasonable games (allowing repeats)
        int maxGames = n * (n - 1);
        int m;
        if (rnd.next() < dens) {
            // more games
            int lo = min(5, maxGames);
            m = rnd.next(lo, min(maxGames, 20));
        } else {
            // fewer games
            m = rnd.next(2, min(5, maxGames));
        }
        println(n, m);

        // Score bias parameters
        int biasP = rnd.next(-2, 2);
        int biasQ = rnd.next(-2, 2);
        for (int i = 0; i < m; i++) {
            // pick two distinct teams
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) b++;
            // generate scores with bias
            int p = rnd.wnext(21, biasP);
            int q = rnd.wnext(21, biasQ);
            println(a, b, p, q);
        }
    }
    return 0;
}
