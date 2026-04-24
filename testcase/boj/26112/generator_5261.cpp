#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for biasing n small or large
    int t1 = rnd.any(vector<int>({-1, 0, 1}));
    int n = rnd.wnext(8, t1) + 3;           // n in [3,10], biased by t1
    int p = rnd.next(1, n - 1);
    int q = n - p;

    // Prepare all 52 card types
    vector<string> suits = {"C", "D", "H", "S"};
    vector<string> values = {"2","3","4","5","6","7","8","9","10","A","J","K","Q"};
    vector<string> allTypes;
    for (auto &s : suits)
        for (auto &v : values)
            allTypes.push_back(s + v);

    // Number of distinct card types in the deck
    int dLow = max(1, n / 3);
    int dHigh = n;
    int d = rnd.next(dLow, dHigh);

    // Assign at least 1 to each, distribute the rest to allow duplicates
    vector<int> counts(d, 1);
    int rem = n - d;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, d - 1);
        counts[idx]++;
    }

    // Pick distinct types
    shuffle(allTypes.begin(), allTypes.end());
    vector<string> typeList(allTypes.begin(), allTypes.begin() + d);

    // Build the multiset deck
    vector<string> deck;
    for (int i = 0; i < d; i++) {
        for (int c = 0; c < counts[i]; c++)
            deck.push_back(typeList[i]);
    }

    // Create dealer's deck X by permuting deck with varying modes
    vector<string> X = deck;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        shuffle(X.begin(), X.end());
    } else if (mode == 1) {
        reverse(X.begin(), X.end());
    } else {
        int k = rnd.next(0, n - 1);
        rotate(X.begin(), X.begin() + k, X.end());
    }

    // Split deck into P1 and P2 for the player
    vector<string> tmp = deck;
    shuffle(tmp.begin(), tmp.end());
    vector<string> P1(tmp.begin(), tmp.begin() + p);
    vector<string> P2(tmp.begin() + p, tmp.end());
    // Optionally shuffle inside each
    if (rnd.next(0,1) == 0) shuffle(P1.begin(), P1.end());
    if (rnd.next(0,1) == 0) shuffle(P2.begin(), P2.end());

    // Output
    println(n, p, q);
    println(X);
    println(P1);
    println(P2);

    return 0;
}
