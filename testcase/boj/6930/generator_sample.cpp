#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int x = 1;
    int m = 2;

    if (mode == 0) {
        vector<pair<int, int>> edges = {{1, 2}, {1, 100}, {99, 100}};
        auto chosen = rnd.any(edges);
        x = chosen.first;
        m = chosen.second;
    } else if (mode == 1) {
        m = rnd.next(2, 100);
        vector<int> coprime;
        for (int candidate = 1; candidate < m; ++candidate) {
            if (gcd(candidate, m) == 1) {
                coprime.push_back(candidate);
            }
        }
        x = rnd.any(coprime);
    } else if (mode == 2) {
        vector<pair<int, int>> noInverse;
        for (int candidateM = 2; candidateM <= 100; ++candidateM) {
            for (int candidateX = 1; candidateX < candidateM; ++candidateX) {
                if (gcd(candidateX, candidateM) > 1) {
                    noInverse.emplace_back(candidateX, candidateM);
                }
            }
        }
        auto chosen = rnd.any(noInverse);
        x = chosen.first;
        m = chosen.second;
    } else if (mode == 3) {
        m = rnd.next(2, 20);
        x = rnd.next(1, m - 1);
    } else {
        m = rnd.next(80, 100);
        x = rnd.next(1, m - 1);
    }

    println(x);
    println(m);
    return 0;
}
