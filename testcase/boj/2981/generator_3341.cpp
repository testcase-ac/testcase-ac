#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of values
    int N = rnd.next(2, 10);

    const int MAXV = 1000;
    int G, r, k_max;
    // Choose a random G with varied distribution (small or large)
    int t = rnd.next(-2, 2);
    do {
        G = rnd.wnext(49, t) + 2;  // G in [2..50]
        r = rnd.next(0, G - 1);
        k_max = (MAXV - r) / G;
    } while (k_max < N + 1);  // ensure enough distinct k >=1

    // Build possible k values (avoid k=0 to keep values >=1)
    vector<int> ks;
    for (int k = 1; k <= k_max; ++k) ks.push_back(k);
    shuffle(ks.begin(), ks.end());
    ks.resize(N);

    // Build the actual numbers: a_i = r + k_i * G
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = r + ks[i] * G;
    }
    // Shuffle output order for diversity
    shuffle(a.begin(), a.end());

    // Output
    println(N);
    for (int x : a) println(x);

    return 0;
}
