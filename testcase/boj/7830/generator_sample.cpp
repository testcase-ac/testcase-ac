#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> makeDeck() {
    const string ranks = "23456789TJQKA";
    const string suits = "DCHS";

    vector<string> deck;
    for (char rank : ranks) {
        for (char suit : suits) {
            string card;
            card += rank;
            card += suit;
            deck.push_back(card);
        }
    }
    return deck;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> deck = makeDeck();
    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<string> hand;
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            hand.assign(deck.begin(), deck.begin() + 26);
        } else if (mode == 1) {
            hand.assign(deck.end() - 26, deck.end());
        } else if (mode == 2) {
            vector<int> ranks(13);
            for (int i = 0; i < 13; ++i) ranks[i] = i;
            shuffle(ranks.begin(), ranks.end());
            ranks.resize(rnd.next(7, 8));

            for (int rank : ranks) {
                for (int suit = 0; suit < 4; ++suit) {
                    hand.push_back(deck[rank * 4 + suit]);
                }
            }
            shuffle(hand.begin(), hand.end());
            hand.resize(26);
        } else if (mode == 3) {
            for (int rank = 0; rank < 13; ++rank) {
                vector<string> cards(deck.begin() + rank * 4, deck.begin() + rank * 4 + 4);
                shuffle(cards.begin(), cards.end());
                hand.push_back(cards[0]);
                hand.push_back(cards[1]);
            }
        } else {
            hand = deck;
            shuffle(hand.begin(), hand.end());
            hand.resize(26);
        }

        if (rnd.next(0, 1)) {
            shuffle(hand.begin(), hand.end());
        }
        println(hand);
    }

    return 0;
}
