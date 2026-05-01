#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type for diversity:
    // 0: small random mods
    // 1: large random mods
    // 2: distinct prime mods (coprime CRT)
    // 3: inconsistent pair to force -1
    int t = rnd.next(0, 3);
    vector<pair<int,int>> px;
    px.reserve(3);

    if (t == 0) {
        // small moduli
        for (int i = 0; i < 3; i++) {
            int P = rnd.next(2, 10);
            int X = rnd.next(1, P - 1);
            px.emplace_back(P, X);
        }
    } else if (t == 1) {
        // larger moduli
        for (int i = 0; i < 3; i++) {
            int P = rnd.next(100, 300);
            int X = rnd.next(1, P - 1);
            px.emplace_back(P, X);
        }
    } else if (t == 2) {
        // distinct small primes for guaranteed unique CRT
        vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < 3; i++) {
            int P = primes[i];
            int X = rnd.next(1, P - 1);
            px.emplace_back(P, X);
        }
    } else {
        // force an inconsistent pair so answer is -1
        // pick two moduli sharing gcd g, make remainders disagree mod g
        int g = rnd.next(2, 10);
        int maxA = 300 / g;
        int a = rnd.next(1, maxA);
        int b = rnd.next(1, maxA);
        int P1 = g * a;
        int P2 = g * b;
        // pick X1 freely
        int X1 = rnd.next(1, P1 - 1);
        // pick X2 so that X2 % g != X1 % g
        vector<int> cand;
        for (int x = 1; x < P2; x++) {
            if (x % g != X1 % g) cand.push_back(x);
        }
        int X2 = rnd.any(cand);
        // third modulus random
        int P3 = rnd.next(2, 300);
        int X3 = rnd.next(1, P3 - 1);
        px.emplace_back(P1, X1);
        px.emplace_back(P2, X2);
        px.emplace_back(P3, X3);
    }

    // shuffle the three (P,X) pairs so positions vary
    shuffle(px.begin(), px.end());

    // output P1 P2 P3 X1 X2 X3
    printf("%d %d %d %d %d %d\n",
        px[0].first, px[1].first, px[2].first,
        px[0].second, px[1].second, px[2].second
    );

    return 0;
}
