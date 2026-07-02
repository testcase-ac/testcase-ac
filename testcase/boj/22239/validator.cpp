#include "testlib.h"

#include <map>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int c = inf.readInt(n, 20000, "C");
    inf.readEoln();

    map<long long, int> resultCount;
    for (int i = 0; i < c; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long value = inf.readLong(1LL, 1000000000LL, "result_i");
        ++resultCount[value];
    }
    inf.readEoln();

    int repeatedOccurrences = 0;
    for (const auto& [value, count] : resultCount) {
        if (count >= 2) {
            repeatedOccurrences += count;
        }
    }
    ensuref(repeatedOccurrences <= 6,
            "sum of occurrences of duplicated result values is %d", repeatedOccurrences);

    vector<int> seenCard(c + 1, 0);
    int totalConstraintCards = 0;
    for (int person = 1; person <= n; ++person) {
        int k = inf.readInt(1, c, "K_i");
        totalConstraintCards += k;
        ensuref(totalConstraintCards <= c,
                "too many cards in constraints after person %d: %d", person, totalConstraintCards);
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int card = inf.readInt(1, c, "card_id");
            ensuref(!seenCard[card],
                    "card %d appears in multiple constraints", card);
            seenCard[card] = person;
        }
        inf.readEoln();
    }
    ensuref(totalConstraintCards == c,
            "constraint card count sum is %d, expected %d", totalConstraintCards, c);

    for (int card = 1; card <= c; ++card) {
        ensuref(seenCard[card], "card %d does not appear in any constraint", card);

        // CHECK: The prose shows "add c", but the official samples use uppercase "ADD".
        string op = inf.readToken("ADD", "operation");
        (void)op;
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "card_value");
        inf.readEoln();
    }

    inf.readEof();
}
