#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Number of rounds N (so 2^N players)
        int N = rnd.next(1, 3);
        int tot = 1 << N;
        // Scenario: 0 = random distribution, 1 = extreme (all same), 2 = balanced-ish
        int scenario = rnd.next(0, 2);
        vector<int> v;
        if (scenario == 0) {
            // Random assignment of each player's preference
            for (int i = 0; i < tot; ++i)
                v.push_back(rnd.next(0, 2));
        } else if (scenario == 1) {
            // All players same type
            int t = rnd.next(0, 2);
            v.assign(tot, t);
        } else {
            // Balanced-ish: floor(tot/3) of each for rock/paper, rest scissors
            int c0 = tot / 3;
            int c1 = tot / 3;
            int c2 = tot - c0 - c1;
            v.insert(v.end(), c0, 0);
            v.insert(v.end(), c1, 1);
            v.insert(v.end(), c2, 2);
        }
        // Shuffle lineup to mix counts
        shuffle(v.begin(), v.end());
        int R = 0, P = 0, S = 0;
        for (int x : v) {
            if (x == 0) ++R;
            else if (x == 1) ++P;
            else ++S;
        }
        // Output N R P S
        println(N, R, P, S);
    }
    return 0;
}
