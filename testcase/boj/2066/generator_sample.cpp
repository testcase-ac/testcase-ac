#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Deck = vector<string>;

Deck makeDeck() {
    const string ranks = "6789TJQKA";
    const string suits = "SCDH";
    Deck deck;
    for (char rank : ranks) {
        for (char suit : suits) {
            deck.push_back(string() + rank + suit);
        }
    }
    return deck;
}

void printPiles(const Deck& deck) {
    for (int row = 0; row < 9; ++row) {
        vector<string> line;
        for (int col = 0; col < 4; ++col) {
            line.push_back(deck[row * 4 + col]);
        }
        println(line);
    }
}

Deck rankClusteredDeck() {
    Deck deck = makeDeck();
    for (int block = 0; block < 9; ++block) {
        int start = block * 4;
        shuffle(deck.begin() + start, deck.begin() + start + 4);
    }
    if (rnd.next(2) == 0) {
        vector<int> order(9);
        for (int i = 0; i < 9; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        Deck reordered;
        for (int idx : order) {
            for (int col = 0; col < 4; ++col) {
                reordered.push_back(deck[idx * 4 + col]);
            }
        }
        deck = reordered;
    }
    return deck;
}

Deck suitLayeredDeck() {
    const string ranks = "6789TJQKA";
    string suits = "SCDH";
    shuffle(suits.begin(), suits.end());

    Deck deck;
    for (char suit : suits) {
        vector<string> layer;
        for (char rank : ranks) {
            layer.push_back(string() + rank + suit);
        }
        shuffle(layer.begin(), layer.end());
        for (const string& card : layer) deck.push_back(card);
    }
    return deck;
}

Deck topPatternDeck() {
    Deck deck = makeDeck();
    shuffle(deck.begin(), deck.end());

    vector<int> topSlots;
    for (int row = 0; row < 9; ++row) topSlots.push_back(row * 4 + 3);

    if (rnd.next(2) == 0) {
        vector<string> tops;
        const string ranks = "6789TJQKA";
        for (char rank : ranks) {
            vector<string> cards;
            for (const string& card : deck) {
                if (card[0] == rank) cards.push_back(card);
            }
            shuffle(cards.begin(), cards.end());
            tops.push_back(cards[0]);
        }
        shuffle(tops.begin(), tops.end());
        for (int i = 0; i < 9; ++i) {
            int pos = int(find(deck.begin(), deck.end(), tops[i]) - deck.begin());
            swap(deck[pos], deck[topSlots[i]]);
        }
    } else {
        char heavyRank = "6789TJQKA"[rnd.next(9)];
        vector<string> heavy;
        vector<string> other;
        for (const string& card : deck) {
            if (card[0] == heavyRank) {
                heavy.push_back(card);
            } else {
                other.push_back(card);
            }
        }
        shuffle(heavy.begin(), heavy.end());
        shuffle(other.begin(), other.end());
        for (int i = 0; i < 4; ++i) {
            int pos = int(find(deck.begin(), deck.end(), heavy[i]) - deck.begin());
            swap(deck[pos], deck[topSlots[i]]);
        }
    }

    return deck;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    Deck deck;
    int mode = rnd.next(4);
    if (mode == 0) {
        deck = makeDeck();
        shuffle(deck.begin(), deck.end());
    } else if (mode == 1) {
        deck = rankClusteredDeck();
    } else if (mode == 2) {
        deck = suitLayeredDeck();
    } else {
        deck = topPatternDeck();
    }

    printPiles(deck);
    return 0;
}
