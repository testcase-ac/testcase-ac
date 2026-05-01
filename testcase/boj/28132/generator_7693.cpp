#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of vectors
    int N = rnd.next(1, 15);

    // Optionally include a zero vector to test special case
    int zeroCount = rnd.next(0, 1);
    vector<pair<ll,ll>> vs;
    if (zeroCount == 1) {
        vs.emplace_back(0, 0);
    }

    // Decide how many guaranteed orthogonal pairs to include
    int rem = N - zeroCount;
    int maxPairs = rem / 2;
    int K = (maxPairs > 0 ? rnd.next(0, min(3, maxPairs)) : 0);

    // Generate K orthogonal pairs
    for (int i = 0; i < K; i++) {
        ll x, y;
        do {
            x = rnd.next(-5, 5);
            y = rnd.next(-5, 5);
        } while (x == 0 && y == 0);
        vs.emplace_back(x, y);
        // Perpendicular vector
        vs.emplace_back(-y, x);
    }

    // Fill remaining with random non-zero vectors
    int rem2 = rem - 2*K;
    vector<int> ranges{5, 10, 20};
    int R = rnd.any(ranges);
    for (int i = 0; i < rem2; i++) {
        ll x, y;
        do {
            x = rnd.next(-R, R);
            y = rnd.next(-R, R);
        } while (x == 0 && y == 0);
        vs.emplace_back(x, y);
    }

    // Shuffle to mix guaranteed pairs and random vectors
    shuffle(vs.begin(), vs.end());

    // Output
    println(N);
    for (auto &p : vs) {
        println(p.first, p.second);
    }

    return 0;
}
