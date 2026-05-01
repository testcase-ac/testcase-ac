#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of gates
    int G = rnd.next(1, 20);
    // Number of planes
    int P = rnd.next(1, G * 2 + 1);

    // Choose a sequence generation pattern: 0=random, 1=ascending, 2=descending
    int pattern = rnd.next(0, 2);
    vector<int> gi;
    gi.reserve(P);
    for (int i = 0; i < P; i++) {
        // With some probability, pick an extreme to create clusters
        if (rnd.next(1, 5) == 1) {
            gi.push_back(rnd.next() < 0.5 ? 1 : G);
        } else {
            gi.push_back(rnd.next(1, G));
        }
    }

    if (pattern == 1) {
        sort(gi.begin(), gi.end());
    } else if (pattern == 2) {
        sort(gi.begin(), gi.end(), greater<int>());
    }

    // Output
    println(G);
    println(P);
    for (int x : gi) {
        println(x);
    }
    return 0;
}
