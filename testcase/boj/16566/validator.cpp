#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 4000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readSpace();
    int K = inf.readInt(1, min(M, 10000), "K");
    inf.readEoln();

    // Read M distinct integers in [1, N]
    vector<int> blue_cards = inf.readInts(M, 1, N, "blue_card");
    inf.readEoln();

    // Check all blue_cards are distinct
    {
        set<int> s(blue_cards.begin(), blue_cards.end());
        ensuref((int)s.size() == M, "All blue_cards must be distinct, but found duplicates.");
    }

    // Read K integers in [1, N] (철수가 낼 카드)
    vector<int> chulsoo_cards = inf.readInts(K, 1, N, "chulsoo_card");
    inf.readEoln();

    // Global property: For every chulsoo_card[i], there must exist a blue_card > chulsoo_card[i] that hasn't been used in previous rounds
    // (since "민수가 카드를 내지 못하는 경우는 없다고 가정한다")
    // So, we need to check that for each chulsoo_card[i], there is at least one unused blue_card > chulsoo_card[i]
    // and that we never run out of blue_cards during the K rounds.

    // We'll simulate 민수's card usage
    multiset<int> available(blue_cards.begin(), blue_cards.end());
    for (int i = 0; i < K; ++i) {
        int c = chulsoo_cards[i];
        // Find the smallest blue_card > c
        auto it = available.upper_bound(c);
        ensuref(it != available.end(),
            "At round %d, 민수 cannot play a card greater than 철수's card %d. (No available blue_card > %d)", i+1, c, c);
        // Remove the card from available
        available.erase(it);
    }

    inf.readEof();
}
