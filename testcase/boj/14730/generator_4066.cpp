#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of terms
    int N = rnd.next(1, 10);
    // Ensure we have at least N distinct degrees
    int Dmin = N - 1;
    int Dmax = rnd.next(Dmin, N * 5);

    // Build degree pool and pick N distinct degrees
    vector<int> allK;
    for (int k = 0; k <= Dmax; ++k) {
        allK.push_back(k);
    }
    shuffle(allK.begin(), allK.end());
    vector<int> Ks(allK.begin(), allK.begin() + N);
    sort(Ks.rbegin(), Ks.rend());  // descending order

    // Coefficient bounds for diversity
    int c_lo = rnd.next(-10, -1);
    int c_hi = rnd.next(1, 10);

    // Build terms
    vector<pair<int,int>> terms;
    for (int k : Ks) {
        int C;
        if (rnd.next() < 0.5) {
            C = rnd.next(c_lo, -1);
        } else {
            C = rnd.next(1, c_hi);
        }
        terms.emplace_back(C, k);
    }

    // Output
    println(N);
    for (auto &p : terms) {
        println(p.first, p.second);
    }
    return 0;
}
