#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small number of pies
    int N = rnd.next(1, 10);
    // Max tastiness bounds
    int bmax = rnd.next(1, 10);
    int emax = rnd.next(1, 10);
    // Difference bound
    int D = rnd.next(0, max(bmax, emax) * 2);
    // Generate Bessie's pies: (B_taste, E_taste)
    vector<pair<int,int>> B(N);
    for (int i = 0; i < N; i++) {
        B[i].first  = rnd.next(0, bmax);
        B[i].second = rnd.next(0, emax);
    }
    // Generate Elsie's pies: (B_taste, E_taste)
    vector<pair<int,int>> E(N);
    for (int i = 0; i < N; i++) {
        E[i].first  = rnd.next(0, bmax);
        E[i].second = rnd.next(0, emax);
    }
    // Ensure at least one Bessie's pie has E_taste = 0 (Elsie can terminate)
    int idxEzero = rnd.next(0, N-1);
    B[idxEzero].second = 0;
    // Ensure at least one Elsie's pie has B_taste = 0 (Bessie can terminate)
    int idxBzero = rnd.next(0, N-1);
    E[idxBzero].first = 0;
    // Introduce some duplicate B_tastes among Bessie's pies for tie cases
    int mdupB = rnd.next(0, min(N, 3));
    for (int k = 0; k < mdupB; k++) {
        int i1 = rnd.next(0, N-1), i2 = rnd.next(0, N-1);
        B[i1].first = B[i2].first;
    }
    // Introduce some duplicate E_tastes among Elsie's pies for tie cases
    int mdupE = rnd.next(0, min(N, 3));
    for (int k = 0; k < mdupE; k++) {
        int j1 = rnd.next(0, N-1), j2 = rnd.next(0, N-1);
        E[j1].second = E[j2].second;
    }
    // Shuffle order to randomize positions of zeros and duplicates
    shuffle(B.begin(), B.end());
    shuffle(E.begin(), E.end());
    // Output
    println(N, D);
    for (auto &p : B) {
        println(p.first, p.second);
    }
    for (auto &p : E) {
        println(p.first, p.second);
    }
    return 0;
}
