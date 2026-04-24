#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(2, 10);
    int B = rnd.next(1, 10);

    // Snow depths
    int maxf = rnd.next(1, 10);
    vector<int> f(N);
    f[0] = 0;
    f[N-1] = 0;
    for (int i = 1; i < N-1; i++) {
        if (rnd.next() < 0.2)
            f[i] = 0;
        else
            f[i] = rnd.next(1, maxf);
    }

    // Hyper-parameters for boots diversity
    int t1 = rnd.next(0, B);
    int t2 = rnd.next(0, B - t1);
    vector<pair<int,int>> boots;

    // Type 1: long step, low snow tolerance
    for (int i = 0; i < t1; i++) {
        int s = rnd.wnext(maxf+1, -1);
        int d = rnd.next(max(1, N/2), N-1);
        boots.emplace_back(s, d);
    }
    // Type 2: high tolerance, small step
    for (int i = 0; i < t2; i++) {
        int s = rnd.next(maxf/2, maxf);
        int d = rnd.wnext(N-1, -1);
        if (d < 1) d = 1;
        boots.emplace_back(s, d);
    }
    // Type 3: fully random
    for (int i = 0; i < B - t1 - t2; i++) {
        int s = rnd.next(0, maxf);
        int d = rnd.next(1, N-1);
        boots.emplace_back(s, d);
    }

    // Shuffle boot order
    shuffle(boots.begin(), boots.end());

    // Output
    println(N, B);
    println(f);
    for (auto &p : boots)
        println(p.first, p.second);

    return 0;
}
