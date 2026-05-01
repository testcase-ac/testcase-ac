#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int scen = rnd.next(0, 3);
    int N;
    vector<int> a;
    if (scen == 0) {
        // Trivial case N=1
        N = 1;
        a.push_back(0);
    } else if (scen == 1) {
        // Small N, fully random
        N = rnd.next(2, 5);
        for (int i = 0; i < 2*N - 1; i++)
            a.push_back(rnd.next(N));
    } else if (scen == 2) {
        // Medium N, skewed distribution towards a favorite residue
        N = rnd.next(6, 15);
        int fav = rnd.next(N);
        for (int i = 0; i < 2*N - 1; i++) {
            if (rnd.next() < 0.6) a.push_back(fav);
            else a.push_back(rnd.next(N));
        }
    } else {
        // Larger N, ensure a valid subset by construction
        N = rnd.next(16, 30);
        vector<int> sol(N);
        int sum = 0;
        for (int i = 0; i < N - 1; i++) {
            sol[i] = rnd.next(N);
            sum = (sum + sol[i]) % N;
        }
        sol[N - 1] = (N - sum) % N;
        a = sol;
        for (int i = 0; i < N - 1; i++)
            a.push_back(rnd.next(N));
    }
    shuffle(a.begin(), a.end());
    println(N);
    println(a);
    return 0;
}
