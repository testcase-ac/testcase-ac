#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int scenario = rnd.next(0, 3);

    int N, K;
    vector<int> w;

    if (scenario == 0) {
        // Very small random
        N = rnd.next(2, 5);
        K = rnd.next(1, 100);
        for (int i = 0; i < N; i++)
            w.push_back(rnd.next(1, K));
    }
    else if (scenario == 1) {
        // Moderate random
        N = rnd.next(6, 20);
        K = rnd.next(50, 200);
        for (int i = 0; i < N; i++)
            w.push_back(rnd.next(1, K));
    }
    else if (scenario == 2) {
        // Complementary pairs that sum exactly to K
        N = rnd.next(4, 40);
        if (N % 2 == 1) N++;
        K = rnd.next(10, 200);
        for (int i = 0; i < N/2; i++) {
            int a = rnd.next(1, K-1);
            int b = K - a;
            w.push_back(a);
            w.push_back(b);
        }
    }
    else {
        // Mix of heavy and light weights
        N = rnd.next(5, 30);
        K = rnd.next(10, 500);
        int heavy = rnd.next(1, max(1, N/5));
        int light = N - heavy;
        for (int i = 0; i < heavy; i++) {
            w.push_back(rnd.next(max(1, K-5), K));
        }
        int up = max(1, K/2);
        for (int i = 0; i < light; i++) {
            w.push_back(rnd.next(1, up));
        }
    }

    shuffle(w.begin(), w.end());
    println(N, K);
    println(w);

    return 0;
}
