#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    set<int> chosen;

    if (mode == 0) {
        chosen.insert(rnd.next(3, 35));
    } else if (mode == 1) {
        int len = rnd.next(1, 12);
        int start = rnd.next(3, 36 - len);
        for (int x = start; x < start + len; ++x) {
            chosen.insert(x);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 16);
        int parity = rnd.next(0, 1);
        vector<int> candidates;
        for (int x = 3; x <= 35; ++x) {
            if (x % 2 == parity) {
                candidates.push_back(x);
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < n && i < int(candidates.size()); ++i) {
            chosen.insert(candidates[i]);
        }
    } else if (mode == 3) {
        int groups = rnd.next(2, 6);
        int current = rnd.next(3, 8);
        for (int g = 0; g < groups && current <= 35; ++g) {
            int len = rnd.next(1, min(5, 36 - current));
            for (int x = current; x < current + len; ++x) {
                chosen.insert(x);
            }
            current += len + rnd.next(1, 4);
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 24);
        vector<int> deck;
        for (int x = 3; x <= 35; ++x) {
            deck.push_back(x);
        }
        shuffle(deck.begin(), deck.end());
        for (int i = 0; i < n; ++i) {
            chosen.insert(deck[i]);
        }
    } else {
        for (int x = 3; x <= 35; ++x) {
            chosen.insert(x);
        }
        int removals = rnd.next(0, 8);
        for (int i = 0; i < removals; ++i) {
            chosen.erase(rnd.next(3, 35));
        }
    }

    vector<int> cards(chosen.begin(), chosen.end());
    println(int(cards.size()));
    println(cards);

    return 0;
}
