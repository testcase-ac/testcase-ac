#include "testlib.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, p, q
    int n = inf.readInt(3, 500, "n");
    inf.readSpace();
    int p = inf.readInt(1, n-1, "p");
    inf.readSpace();
    int q = inf.readInt(1, n-1, "q");
    inf.readEoln();
    ensuref(p + q == n, "The sum p+q must equal n, but got p=%d, q=%d, n=%d", p, q, n);

    // Helper to read and validate a line of cards
    auto readDeck = [&](int cnt, const string &name, vector<string> &deck) {
        deck.resize(cnt);
        for (int i = 0; i < cnt; i++) {
            deck[i] = inf.readToken("[^ ]+", name.c_str());
            if (i + 1 < cnt) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // Validate format of the card token
            string &tok = deck[i];
            int L = (int)tok.size();
            ensuref(L >= 2 && L <= 3,
                    "%s[%d] has invalid length %d (must be 2 or 3)", 
                    name.c_str(), i, L);
            char suit = tok[0];
            ensuref(suit == 'C' || suit == 'D' || suit == 'H' || suit == 'S',
                    "%s[%d] has invalid suit '%c'", name.c_str(), i, suit);
            string rank = tok.substr(1);
            bool okRank = false;
            static const string ranks[] = {
                "2","3","4","5","6","7","8","9","10","A","J","K","Q"
            };
            for (auto &r: ranks) if (rank == r) { okRank = true; break; }
            ensuref(okRank, "%s[%d] has invalid rank \"%s\"", 
                    name.c_str(), i, rank.c_str());
        }
    };

    vector<string> X, P1, P2;
    readDeck(n,  "X",  X);
    readDeck(p, "P1", P1);
    readDeck(q, "P2", P2);

    // Check that P1+P2 is exactly a permutation (multiset) of X
    map<string,int> cnt;
    for (auto &c : X)  cnt[c] += 1;
    for (auto &c : P1) cnt[c] -= 1;
    for (auto &c : P2) cnt[c] -= 1;
    for (auto &kv : cnt) {
        const string &card = kv.first;
        int diff = kv.second;
        ensuref(diff == 0, 
                "Card count mismatch for \"%s\": net count = %d (should be 0)", 
                card.c_str(), diff);
    }

    inf.readEof();
    return 0;
}
