#include "testlib.h"
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M;
    double r = rnd.next();
    if (r < 0.33) {
        // Tall shapes: ensure N >= M
        int N0 = rnd.next(1, 25);
        int hiM = 25 / N0;  // hiM >= 1
        int M0 = rnd.next(1, hiM);
        N = N0; M = M0;
        if (M > N) swap(N, M);
    }
    else if (r < 0.66) {
        // Wide shapes: ensure M >= N
        int M0 = rnd.next(1, 25);
        int hiN = 25 / M0;  // hiN >= 1
        int N0 = rnd.next(1, hiN);
        N = N0; M = M0;
        if (N > M) swap(N, M);
    }
    else {
        // Balanced shapes via factors of a random area
        int area = rnd.next(1, 25);
        vector<pair<int,int>> fac;
        for (int i = 1; i * i <= area; ++i) {
            if (area % i == 0) {
                fac.emplace_back(i, area / i);
                if (i != area / i)
                    fac.emplace_back(area / i, i);
            }
        }
        auto pr = rnd.any(fac);
        N = pr.first;
        M = pr.second;
    }

    // Finally ensure constraints 1 <= N,M and N*M <= 25
    // (they are guaranteed by construction)

    println(N, M);
    return 0;
}
