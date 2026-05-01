#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias small or large
    int tN = rnd.next(-1, 1);
    int baseN = rnd.wnext(13, tN); // 0..12
    int N = baseN + 2;             // 2..14

    // Hyper-parameter for L: ensure L > N, up to 50
    int tL = rnd.next(-1, 1);
    int L = rnd.wnext(50 - N, tL) + (N + 1); // N+1 .. 50

    // Generate distinct positions in (0, L)
    vector<int> posPool;
    for (int x = 1; x < L; x++) posPool.push_back(x);
    shuffle(posPool.begin(), posPool.end());
    posPool.resize(N);
    sort(posPool.begin(), posPool.end());

    // Hyper-parameter for weight bias
    int tW = rnd.next(-2, 2);

    // Hyper-parameter for direction bias (probability of moving left)
    double pLeft = rnd.next(0.0, 1.0);

    // Build cows
    struct Cow { int w, x, d; };
    vector<Cow> cows;
    cows.reserve(N);
    for (int i = 0; i < N; i++) {
        int w = rnd.wnext(100, tW) + 1;       // weight 1..100
        int x = posPool[i];
        int d = (rnd.next() < pLeft ? -1 : 1);
        cows.push_back({w, x, d});
    }

    // Shuffle to avoid sorted order by position
    shuffle(cows.begin(), cows.end());

    // Output
    println(N, L);
    for (auto &c : cows) {
        println(c.w, c.x, c.d);
    }

    return 0;
}
