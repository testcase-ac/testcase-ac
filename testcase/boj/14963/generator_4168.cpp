#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N_target = rnd.next(1, 10);       // desired number of draws (at least 1)
    bool stopEarly = rnd.next(0, 1);      // whether to randomly stop early (but not before first draw)
    int biasMode = rnd.next(-1, 1);       // -1: favor low cards, 0: uniform, 1: favor high cards

    // Build the full deck: 4 copies of 2..9, 16 tens, 4 aces (11)
    vector<int> deckList;
    for (int v = 2; v <= 9; ++v)
        for (int i = 0; i < 4; ++i)
            deckList.push_back(v);
    for (int i = 0; i < 16; ++i)
        deckList.push_back(10);
    for (int i = 0; i < 4; ++i)
        deckList.push_back(11);

    vector<int> draws;
    int sum = 0;
    // Draw cards without replacement, keeping total sum ≤ 21
    while ((int)draws.size() < N_target) {
        // collect indices of cards that keep sum ≤ 21
        vector<int> validIdx;
        for (int i = 0; i < (int)deckList.size(); ++i) {
            if (sum + deckList[i] <= 21)
                validIdx.push_back(i);
        }
        if (validIdx.empty()) break;
        // optional random early stop, but not before at least one draw
        if (stopEarly && !draws.empty() && rnd.next(0, 9) == 0) break;

        // sort candidates by card value (increasing)
        sort(validIdx.begin(), validIdx.end(), [&](int a, int b) {
            return deckList[a] < deckList[b];
        });
        int sz = validIdx.size();
        int pos;
        if (biasMode > 0) {
            // favor higher card values
            pos = rnd.wnext(sz, biasMode);
        } else if (biasMode < 0) {
            // favor lower card values
            pos = rnd.wnext(sz, biasMode);
        } else {
            // uniform choice
            pos = rnd.next(sz - 1);
        }
        int idx = validIdx[pos];
        int v = deckList[idx];
        // remove chosen card from deck
        deckList[idx] = deckList.back();
        deckList.pop_back();
        draws.push_back(v);
        sum += v;
    }

    // Guarantee at least one draw
    if (draws.empty()) {
        int idx = rnd.next((int)deckList.size() - 1);
        draws.push_back(deckList[idx]);
    }

    // Output the test case
    int N = draws.size();
    println(N);
    for (int v : draws)
        println(v);

    return 0;
}
