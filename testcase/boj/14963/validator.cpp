#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cards drawn so far
    int N = inf.readInt(1, 52, "N");
    inf.readEoln();

    // Prepare count array for values 0..11 (we'll use indices 2..11)
    vector<int> cnt(12, 0);
    long long sum = 0;

    // Read each drawn card value
    for (int i = 0; i < N; i++) {
        int v = inf.readInt(2, 11, "card");
        inf.readEoln();
        // Accumulate sum
        sum += v;
        // Count occurrences
        cnt[v]++;
    }

    // The problem guarantees that the sum so far is <= 21
    ensuref(sum <= 21, "Sum of drawn cards must be at most 21, but got %lld", sum);

    // Now check we have not drawn more cards of any value than exist in a standard deck
    // Value 2..9 : 4 cards each
    for (int v = 2; v <= 9; v++) {
        ensuref(cnt[v] <= 4,
                "Too many cards of value %d: drawn %d but at most 4 exist in deck",
                v, cnt[v]);
    }
    // Value 10 : ranks 10, J, Q, K -> total 16 cards
    ensuref(cnt[10] <= 16,
            "Too many cards of value 10: drawn %d but at most 16 exist in deck",
            cnt[10]);
    // Value 11 (Aces) : 4 cards
    ensuref(cnt[11] <= 4,
            "Too many cards of value 11: drawn %d but at most 4 exist in deck",
            cnt[11]);

    // No extra lines or tokens
    inf.readEof();
    return 0;
}
