#include "testlib.h"
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, K, T
    int N = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 30000, "K");
    inf.readSpace();
    int T = inf.readInt(0, 14, "T");
    inf.readEoln();

    // 2. Read Puang's info
    int Xp = inf.readInt(-10000, 10000, "X_p");
    inf.readSpace();
    int Yp = inf.readInt(-10000, 10000, "Y_p");
    inf.readSpace();
    int Vp = inf.readInt(1, 15, "V_p");
    inf.readEoln();

    // 3. Read friends' info
    vector<int> X(N), Y(N), V(N), P(N);
    set<pair<int,int>> coords;
    coords.insert({Xp, Yp});
    for (int i = 0; i < N; ++i) {
        X[i] = inf.readInt(-10000, 10000, "X_i");
        inf.readSpace();
        Y[i] = inf.readInt(-10000, 10000, "Y_i");
        inf.readSpace();
        V[i] = inf.readInt(1, 15, "V_i");
        inf.readSpace();
        P[i] = inf.readInt(0, 1, "P_i");
        inf.readEoln();

        // Check coordinate uniqueness
        ensuref(coords.count({X[i], Y[i]}) == 0,
            "Duplicate coordinates found at friend %d: (%d, %d)", i+1, X[i], Y[i]);
        coords.insert({X[i], Y[i]});
    }

    inf.readEof();
}
