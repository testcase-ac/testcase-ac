#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Pool of possible tree species names (some with spaces)
    vector<string> pool = {
        "Red Alder", "Ash", "Aspen", "Basswood", "Beech", "Yellow Birch",
        "Cherry", "Cottonwood", "Cypress", "Gum", "Hackberry", "White Oak",
        "Hickory", "Pecan", "Hard Maple", "Soft Maple", "Red Elm", "Red Oak",
        "Poplar", "Sassafras", "Sycamore", "Black Walnut", "Willow"
    };

    // Number of distinct species S
    int maxS = min((int)pool.size(), 10);
    int S = rnd.next(2, maxS);

    // Choose S distinct species
    shuffle(pool.begin(), pool.end());
    vector<string> species(pool.begin(), pool.begin() + S);

    // Total number of trees T
    int T = rnd.next(S, S * 4);

    // Distribution type selector
    double mode = rnd.next(0.0, 1.0);
    vector<string> trees;
    trees.reserve(T);

    if (mode < 0.33) {
        // Uniform distribution
        for (int i = 0; i < T; i++) {
            int idx = rnd.next(0, S - 1);
            trees.push_back(species[idx]);
        }
    } else if (mode < 0.66) {
        // One dominant species
        int primary = rnd.next(0, S - 1);
        double p = rnd.next(0.5, 0.9);
        for (int i = 0; i < T; i++) {
            if (rnd.next() < p) {
                trees.push_back(species[primary]);
            } else {
                int idx = rnd.next(0, S - 2);
                if (idx >= primary) idx++;
                trees.push_back(species[idx]);
            }
        }
    } else {
        // Weighted random distribution
        vector<int> w(S);
        for (int i = 0; i < S; i++) {
            w[i] = rnd.next(1, 10);
        }
        vector<int> pref(S);
        pref[0] = w[0];
        for (int i = 1; i < S; i++) pref[i] = pref[i - 1] + w[i];
        int W = pref.back();
        for (int i = 0; i < T; i++) {
            int r = rnd.next(1, W);
            int idx = lower_bound(pref.begin(), pref.end(), r) - pref.begin();
            trees.push_back(species[idx]);
        }
    }

    // Shuffle overall list to mix entries
    shuffle(trees.begin(), trees.end());

    // Output each tree species on its own line
    for (auto &t : trees) {
        println(t);
    }

    return 0;
}
