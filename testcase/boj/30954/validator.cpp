#include "testlib.h"
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(3, 100, "k");
    inf.readEoln();

    vector<int> C(k);
    vector<vector<int>> stacks(k);
    set<int> card_labels;
    int total_capacity = 0;
    int max_capacity = 0;
    int sum_cards = 0;

    for (int i = 0; i < k; ++i) {
        C[i] = inf.readInt(1, n, format("C_%d", i+1));
        total_capacity += C[i];
        max_capacity = max(max_capacity, C[i]);
        stacks[i].resize(C[i]);
        bool seen_empty_slot = false;
        for (int j = 0; j < C[i]; ++j) {
            inf.readSpace();
            int card = inf.readInt(0, n, format("S_%d[%d]", i+1, j+1));
            stacks[i][j] = card;
            if (card != 0) {
                ensuref(!seen_empty_slot,
                        "nonzero card %d appears after an empty slot at stack %d, position %d",
                        card, i+1, j+1);
                ensuref(card_labels.count(card) == 0, "Card label %d appears more than once (at stack %d, position %d)", card, i+1, j+1);
                card_labels.insert(card);
                sum_cards++;
            } else {
                seen_empty_slot = true;
            }
        }
        inf.readEoln();
    }

    ensuref((int)card_labels.size() == n, "Not all cards 1..n are present exactly once. Found %d unique cards, expected %d", (int)card_labels.size(), n);
    for (int i = 1; i <= n; ++i) {
        ensuref(card_labels.count(i), "Card label %d is missing", i);
    }

    ensuref(sum_cards == n, "Total number of nonzero cards is %d, expected %d", sum_cards, n);

    ensuref(n <= total_capacity - max_capacity, "n = %d, sum(C_i) = %d, max(C_i) = %d, but must have n <= sum(C_i) - max(C_i)", n, total_capacity, max_capacity);

    inf.readEof();
}
