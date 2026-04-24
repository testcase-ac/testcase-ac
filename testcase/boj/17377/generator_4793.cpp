#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Taxi parameters
    int A = rnd.next(1, 100);
    int B = rnd.next(1, 100);
    int C = rnd.next(1, 100);

    // Number of points
    int N = rnd.next(4, 10);

    // Prepare candidate names (only letters, no duplicates)
    vector<string> pool = {
        "Alpha","Beta","Gamma","Delta","Epsilon","Zeta","Eta","Theta",
        "Iota","Kappa","Lambda","Mu","Nu","Xi","Omicron","Pi","Rho",
        "Sigma","Tau","Upsilon","Phi","Chi","Psi","Omega"
    };
    shuffle(pool.begin(), pool.end());

    // Build location names, including exactly one "Taxi Garage"
    vector<string> locNames;
    locNames.push_back("Taxi Garage");
    for (int i = 0; i < N - 1; i++) {
        locNames.push_back(pool[i]);
    }
    shuffle(locNames.begin(), locNames.end());
    int garageIdx = find(locNames.begin(), locNames.end(), "Taxi Garage") - locNames.begin();

    // Assign small coordinates [0..10]
    vector<pair<int,int>> coords(N);
    for (int i = 0; i < N; i++) {
        coords[i].first  = rnd.next(0, 10);
        coords[i].second = rnd.next(0, 10);
    }

    // Pick 3 distinct gas stations (cannot be Taxi Garage)
    vector<int> idxs;
    for (int i = 0; i < N; i++) {
        if (i != garageIdx) idxs.push_back(i);
    }
    shuffle(idxs.begin(), idxs.end());
    vector<int> gasIdx = {idxs[0], idxs[1], idxs[2]};
    vector<int> gasPrice(3);
    for (int i = 0; i < 3; i++) {
        gasPrice[i] = rnd.next(1, 100);
    }

    // Generate a sequence of K statements
    int K = rnd.next(1, 10);
    int pos = garageIdx;
    vector<string> statements;
    for (int i = 0; i < K; i++) {
        bool wantPickup = rnd.next(0, 1) == 0;
        if (wantPickup) {
            // Pickup: choose a destination not equal to current or garage
            vector<int> choices;
            for (int j = 0; j < N; j++) {
                if (j != pos && j != garageIdx) choices.push_back(j);
            }
            int d = rnd.any(choices);
            statements.push_back("Pickup a passenger going to " + locNames[d] + ".");
            // position stays the same
        } else {
            // Go to: choose a new position != current
            vector<int> choices;
            for (int j = 0; j < N; j++) {
                if (j != pos) choices.push_back(j);
            }
            int d = rnd.any(choices);
            statements.push_back("Go to " + locNames[d] + ".");
            pos = d;
        }
    }

    // Output all parts
    println(A, B, C);
    println(N);
    for (int i = 0; i < N; i++) {
        println(locNames[i], coords[i].first, coords[i].second);
    }
    for (int i = 0; i < 3; i++) {
        println(locNames[gasIdx[i]], gasPrice[i]);
    }
    println(K);
    for (auto &s : statements) {
        println(s);
    }

    return 0;
}
