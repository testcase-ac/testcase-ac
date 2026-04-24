#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for L bias: small to moderate
    int t = rnd.next(-2, 2);
    long long L = rnd.wnext(19, t) + 2;  // L in [2..20], biased
    // Number of ants
    int maxN = min<long long>(10, 3 * (L - 1));
    int N = rnd.next(1, maxN);

    // Build all possible starting positions
    vector<pair<char, long long>> pos;
    for (char c : {'A', 'B', 'C'})
        for (long long x = 1; x < L; ++x)
            pos.emplace_back(c, x);
    shuffle(pos.begin(), pos.end());
    pos.resize(N);

    // Bias for direction: more inward or outward
    double inwardProb = rnd.next(0.0, 1.0);

    // Assign directions
    vector<int> dir(N);
    for (int i = 0; i < N; i++) {
        dir[i] = (rnd.next() < inwardProb ? 0 : 1);
    }

    // Shuffle the list of ants for random order
    vector<int> idx(N);
    for (int i = 0; i < N; i++) idx[i] = i;
    shuffle(idx.begin(), idx.end());

    // Output
    println(N, L);
    for (int i = 0; i < N; i++) {
        int j = idx[i];
        println(pos[j].first, pos[j].second, dir[j]);
    }
    return 0;
}
