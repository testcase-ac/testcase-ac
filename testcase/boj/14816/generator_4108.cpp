#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int P = rnd.next(2, 4);
        int N = rnd.next(1, 10);
        vector<int> G(N);

        int sce = rnd.next(0, 4);
        if (sce == 0) {
            // fully random sizes
            for (int i = 0; i < N; i++) {
                G[i] = rnd.next(1, 20);
            }
        } else if (sce == 1) {
            // all multiples of P
            for (int i = 0; i < N; i++) {
                int mult = rnd.next(1, 5);
                G[i] = P * mult;
            }
        } else if (sce == 2) {
            // only remainders 1 and P-1
            vector<int> rset;
            rset.push_back(1);
            if (P - 1 != 1) rset.push_back(P - 1);
            for (int i = 0; i < N; i++) {
                int r = rnd.any(rset);
                int x = rnd.next(0, 4);
                G[i] = r + P * x;
                if (G[i] == 0) G[i] = P;
            }
        } else if (sce == 3) {
            // only remainders 0 and some r2
            int r2 = rnd.next(1, P - 1);
            for (int i = 0; i < N; i++) {
                int r = rnd.next(0, 1) ? r2 : 0;
                int x = rnd.next(0, 4);
                G[i] = r + P * x;
                if (G[i] == 0) G[i] = P;
            }
        } else {
            // weighted remainders
            vector<int> w(P);
            for (int i = 0; i < P; i++) {
                w[i] = rnd.next(1, 5);
            }
            int sumw = accumulate(w.begin(), w.end(), 0);
            for (int i = 0; i < N; i++) {
                int x = rnd.next(1, sumw);
                int r = 0;
                for (int j = 0; j < P; j++) {
                    x -= w[j];
                    if (x <= 0) { r = j; break; }
                }
                int x2 = rnd.next(0, 4);
                G[i] = r + P * x2;
                if (G[i] == 0) G[i] = P;
            }
        }

        println(N, P);
        println(G);
    }
    return 0;
}
