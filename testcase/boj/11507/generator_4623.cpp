#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of cards we currently have: between 1 and 20
    int cnt = rnd.next(1, 20);

    // prepare full deck of 52 unique cards
    vector<string> deck;
    const vector<char> suits = {'P','K','H','T'};
    for (char s : suits) {
        for (int num = 1; num <= 13; ++num) {
            char buf[4];
            buf[0] = s;
            buf[1] = '0' + (num / 10);
            buf[2] = '0' + (num % 10);
            buf[3] = '\0';
            deck.push_back(string(buf));
        }
    }
    // shuffle deck for random unique draws
    shuffle(deck.begin(), deck.end());
    int deckPtr = 0;

    // probability to insert a duplicate card
    double dupProb = rnd.next();

    vector<string> cards;
    while ((int)cards.size() < cnt) {
        if (!cards.empty() && rnd.next() < dupProb) {
            // insert a duplicate from existing cards
            cards.push_back(rnd.any(cards));
        } else {
            // take next unique card if available
            if (deckPtr < (int)deck.size()) {
                cards.push_back(deck[deckPtr++]);
            } else {
                // fallback: force duplicate if deck exhausted
                cards.push_back(rnd.any(cards));
            }
        }
    }

    // build the single-line input string
    string S;
    for (auto &c : cards) {
        S += c;
    }

    // output the generated test case
    printf("%s\n", S.c_str());

    return 0;
}
