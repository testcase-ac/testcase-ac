#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int H = rnd.next(1, 10);        // number of days
    int T = rnd.next(1, 6);         // number of teams
    int S = rnd.next(0, 5);         // maximum store label

    double zeroProb = rnd.next(0.0, 1.0);     // probability of no clean store on a day
    int dParam = rnd.next(-1, 1);             // weight parameter for durations
    int iParam = rnd.next(-2, 2);             // weight parameter for incomes

    // Generate C_k: highest clean store each day
    vector<int> C(H);
    for (int k = 0; k < H; k++) {
        if (S == 0 || rnd.next() < zeroProb) {
            C[k] = 0;
        } else {
            C[k] = rnd.next(1, S);
        }
    }

    // Generate teams: duration D_t and income I_t
    vector<pair<int,int>> teams(T);
    for (int t = 0; t < T; t++) {
        int D = rnd.wnext(H, dParam) + 1;     // in [1, H]
        int I = rnd.wnext(101, iParam);       // in [0, 100]
        teams[t] = {D, I};
    }

    // Output
    println(H, T);
    println(C);
    for (auto &p : teams) {
        println(p.first, p.second);
    }
    return 0;
}
