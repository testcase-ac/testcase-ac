#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 10);
        int P = rnd.any(vector<int>{2, 3});
        println(N, P);
        vector<int> G;
        for (int i = 0; i < N; ++i) {
            // choose a remainder with varied bias
            int t = rnd.next(-2, 2);
            int r = rnd.wnext(P, t);  // in [0, P-1]
            int k = rnd.next(0, 4);
            int g = r + k * P;
            if (g < 1) g += P;
            G.push_back(g);
        }
        shuffle(G.begin(), G.end());
        println(G);
    }
    return 0;
}
