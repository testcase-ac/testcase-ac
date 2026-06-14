#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Operation {
    string kind;
    char arg;
};

string formatOperations(const vector<Operation>& operations) {
    string line;
    for (int i = 0; i < (int)operations.size(); ++i) {
        if (i > 0) line += ",";
        line += operations[i].kind;
        line += " ";
        line += operations[i].arg;
    }
    return line;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 9);
    int n = rnd.next(1, c);
    int mode = rnd.next(4);

    vector<int> cards(c);
    iota(cards.begin(), cards.end(), 1);
    shuffle(cards.begin(), cards.end());

    vector<vector<int>> playerCards(n);
    for (int i = 0; i < n; ++i) playerCards[i].push_back(cards[i]);
    for (int i = n; i < c; ++i) playerCards[rnd.next(n)].push_back(cards[i]);
    for (auto& owned : playerCards) shuffle(owned.begin(), owned.end());

    vector<vector<Operation>> operations(c + 1);
    int remaining = 10;
    for (int card = 1; card <= c; ++card) {
        int cardsLeft = c - card + 1;
        int maxHere = min(3, remaining - (cardsLeft - 1));
        int count = rnd.next(1, maxHere);
        remaining -= count;

        for (int j = 0; j < count; ++j) {
            bool useDel = false;
            if (mode == 0) {
                useDel = false;
            } else if (mode == 1) {
                useDel = rnd.next(100) < 70;
            } else if (mode == 2) {
                useDel = (card + j) % 2 == 0;
            } else {
                useDel = rnd.next(2) == 0;
            }

            if (useDel) {
                int digit;
                if (mode == 1 && rnd.next(100) < 45) {
                    digit = rnd.next(5, 9);
                } else {
                    digit = rnd.next(0, min(9, c));
                }
                operations[card].push_back({"DEL", char('0' + digit)});
            } else {
                char ch = char('a' + rnd.next(0, min(25, 2 + c)));
                operations[card].push_back({"ADD", ch});
            }
        }
    }

    if (mode == 2) {
        operations[1] = {{"ADD", 'a'}, {"DEL", '0'}};
        for (int card = 2; card <= c; ++card) {
            if (card % 2 == 0) {
                operations[card] = {{"ADD", char('a' + rnd.next(0, min(25, c)))}};
            } else {
                operations[card] = {{"DEL", char('0' + rnd.next(0, min(9, c)))}};
            }
        }
    } else if (mode == 1) {
        operations[1][0] = {"DEL", char('0' + rnd.next(1, 9))};
    }

    println(n, c);
    for (const auto& owned : playerCards) {
        printf("%d", (int)owned.size());
        for (int card : owned) printf(" %d", card);
        printf("\n");
    }
    for (int card = 1; card <= c; ++card) {
        println(formatOperations(operations[card]));
    }

    return 0;
}
