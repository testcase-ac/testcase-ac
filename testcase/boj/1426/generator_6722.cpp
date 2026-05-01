#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cards/bins
    int N = rnd.next(1, 10);
    // Maximum value for card numbers and bin capacities
    int maxV = rnd.next(2, 20);
    bool possible = rnd.next(0, 1);

    vector<int> w(N), cardValue(N);
    vector<char> cardChar(N);
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (possible) {
        // Generate a guaranteed possible case:
        for (int i = 0; i < N; i++) {
            w[i] = rnd.next(1, maxV);
            cardValue[i] = rnd.next(1, w[i]);
            cardChar[i] = rnd.any(letters);
        }
    } else {
        // Generate a guaranteed impossible case:
        int imp = rnd.next(0, N - 1);
        // Choose a small capacity for the impossible bin
        w[imp] = rnd.next(1, maxV - 1);
        // All cards have values > w[imp], so bin imp cannot take any card
        for (int i = 0; i < N; i++) {
            cardValue[i] = rnd.next(w[imp] + 1, maxV);
            cardChar[i] = rnd.any(letters);
        }
        // Fill other bins arbitrarily
        for (int i = 0; i < N; i++) {
            if (i == imp) continue;
            w[i] = rnd.next(1, maxV);
        }
    }

    // Prepare card list and shuffle for input randomness
    vector<pair<int,char>> cards(N);
    for (int i = 0; i < N; i++) {
        cards[i] = {cardValue[i], cardChar[i]};
    }
    shuffle(cards.begin(), cards.end());

    // Output
    println(N);
    for (auto &p : cards) {
        println(p.first, p.second);
    }
    println(w);

    return 0;
}
