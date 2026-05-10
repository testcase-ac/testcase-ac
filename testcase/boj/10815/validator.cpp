#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cards N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read the N distinct card values
    vector<int> cards = inf.readInts(N, -10000000, 10000000, "cards");
    inf.readEoln();

    // Ensure no duplicates among the cards
    sort(cards.begin(), cards.end());
    for (int i = 1; i < N; i++) {
        ensuref(cards[i] != cards[i-1],
                "Duplicate card detected: value %d appears at least twice", cards[i]);
    }

    // Read number of queries M
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read the M query values
    vector<int> queries = inf.readInts(M, -10000000, 10000000, "queries");
    inf.readEoln();

    // No further global constraints (queries may repeat)

    inf.readEof();
    return 0;
}
