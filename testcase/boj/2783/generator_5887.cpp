#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base store price: X won per Y grams
    int X = rnd.next(1, 100);
    int Y = rnd.next(1, 1000);

    // Decide if we force at least one cheaper competitor or none
    bool needCheaper = rnd.next(0, 1) == 0;

    // Choose N with bias both small and large occasionally
    vector<int> bias = {-2, -1, 1, 2};
    int t = rnd.any(bias);
    int N = rnd.wnext(100, t) + 1;  // yields 1..100

    // Generate competitors
    vector<pair<int,int>> comps;
    if (needCheaper) {
        // Ensure at least one is strictly cheaper
        int idxCheaper = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++) {
            if (i == idxCheaper) {
                // Create a competitor with cost < X/Y
                int xi, yi;
                for (;;) {
                    yi = rnd.next(1, 1000);
                    long long cap = (1LL * X * yi - 1) / Y;
                    if (cap >= 1) {
                        int upper = cap < 100 ? (int)cap : 100;
                        xi = rnd.next(1, upper);
                        break;
                    }
                }
                comps.emplace_back(xi, yi);
            } else {
                // Random unconstrained competitor
                int xi = rnd.next(1, 100);
                int yi = rnd.next(1, 1000);
                comps.emplace_back(xi, yi);
            }
        }
    } else {
        // Ensure no competitor is cheaper (all Xi/Yi >= X/Y)
        for (int i = 0; i < N; i++) {
            int xi, yi;
            for (;;) {
                yi = rnd.next(1, 1000);
                long long minXi = (1LL * X * yi + Y - 1) / Y;
                if (minXi <= 100) {
                    xi = rnd.next((int)minXi, 100);
                    break;
                }
            }
            comps.emplace_back(xi, yi);
        }
    }

    // Shuffle to avoid positional biases
    shuffle(comps.begin(), comps.end());

    // Output
    println(X, Y);
    println(N);
    for (auto &p : comps) {
        println(p.first, p.second);
    }

    return 0;
}
