#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide outcome type: 0 = Tie, 1 = A win, 2 = B win
    int outcome = rnd.next(0, 2);
    int V, countA, countB;

    if (outcome == 0) {
        // Tie: need even V >= 2
        vector<int> evens;
        for (int i = 2; i <= 15; i += 2)
            evens.push_back(i);
        V = rnd.any(evens);
        countA = V / 2;
        countB = V / 2;
    } else {
        // A win or B win
        V = rnd.next(1, 15);
        int half = V / 2;  // floor(V/2)
        if (outcome == 1) {
            // A wins: countA > half
            countA = rnd.next(half + 1, V);
            countB = V - countA;
        } else {
            // B wins
            countB = rnd.next(half + 1, V);
            countA = V - countB;
        }
    }

    // Build and shuffle votes
    vector<char> votes;
    votes.reserve(V);
    for (int i = 0; i < countA; i++) votes.push_back('A');
    for (int i = 0; i < countB; i++) votes.push_back('B');
    shuffle(votes.begin(), votes.end());

    // Output
    println(V);
    for (char c : votes) printf("%c", c);
    printf("\n");

    return 0;
}
