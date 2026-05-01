#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of tourists: sometimes trivial 1, usually 2-6
    int N = (rnd.next(0, 9) == 0 ? 1 : rnd.next(2, 6));
    // Bit-length for coordinates (kept small for hand verification)
    int L = rnd.next(1, 6);
    vector<pair<int,int>> a;
    a.reserve(N);
    for (int i = 0; i < N; i++) {
        // Occasionally duplicate a previous tourist position
        if (i > 0 && rnd.next(0, 4) == 0) {
            a.push_back(a[rnd.next(0, i - 1)]);
        } else {
            // Generate X in [0, 2^L - 1]
            int maxv = (1 << L) - 1;
            int X = rnd.next(0, maxv);
            // Generate Y bitwise so that X & Y == 0
            int Y = 0;
            for (int b = 0; b < L; b++) {
                if (!(X & (1 << b)) && rnd.next(0, 1)) {
                    Y |= 1 << b;
                }
            }
            a.emplace_back(X, Y);
        }
    }
    // Output
    println(N);
    for (auto &p : a) {
        println(p.first, p.second);
    }
    return 0;
}
