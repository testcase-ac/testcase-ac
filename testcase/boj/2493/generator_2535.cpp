/* generator code */
#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of towers
    int N = rnd.next(1, 10);
    // Choose a random maximum height for diversity
    vector<int> maxOptions = {20, 100, 1000, 100000000};
    int hiMax = rnd.any(maxOptions);
    // Generate N distinct heights in [1, hiMax]
    set<int> S;
    while ((int)S.size() < N) {
        S.insert(rnd.next(1, hiMax));
    }
    vector<int> h(S.begin(), S.end());
    // Shuffle to randomize positions
    shuffle(h.begin(), h.end());
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%d%c", h[i], i+1==N? '\n' : ' ');
    }
    return 0;
}
