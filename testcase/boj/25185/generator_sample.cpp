#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string card(int number, char suit) {
    return to_string(number) + suit;
}

char randomSuit() {
    const string suits = "mps";
    return suits[rnd.next(0, 2)];
}

string randomCard() {
    return card(rnd.next(1, 9), randomSuit());
}

void shuffleAndPrint(vector<string> cards) {
    shuffle(cards.begin(), cards.end());
    println(cards);
}

vector<string> makeCase() {
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        char suit = randomSuit();
        int start = rnd.next(1, 7);
        vector<string> cards = {
            card(start, suit),
            card(start + 1, suit),
            card(start + 2, suit),
            randomCard(),
        };
        return cards;
    }

    if (mode == 1) {
        string repeated = randomCard();
        vector<string> cards = {repeated, repeated, repeated, randomCard()};
        return cards;
    }

    if (mode == 2) {
        string first = randomCard();
        string second = randomCard();
        while (second == first) {
            second = randomCard();
        }
        vector<string> cards = {first, first, second, second};
        return cards;
    }

    if (mode == 3) {
        string repeated = randomCard();
        vector<string> cards = {repeated, repeated, repeated, repeated};
        return cards;
    }

    if (mode == 4) {
        char suit = randomSuit();
        int start = rnd.next(1, 7);
        vector<string> cards = {
            card(start, suit),
            card(start + 1, suit),
            card(start + 2, randomSuit()),
            randomCard(),
        };
        return cards;
    }

    if (mode == 5) {
        int number = rnd.next(1, 9);
        vector<string> cards = {
            card(number, 'm'),
            card(number, 'p'),
            card(number, 's'),
            randomCard(),
        };
        return cards;
    }

    if (mode == 6) {
        char suit = randomSuit();
        int a = rnd.next(1, 6);
        int b = rnd.next(a + 3, 9);
        vector<string> cards = {
            card(a, suit),
            card(a + 1, suit),
            card(b, suit),
            randomCard(),
        };
        return cards;
    }

    vector<string> cards;
    for (int i = 0; i < 4; ++i) {
        cards.push_back(randomCard());
    }
    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 40);
    println(t);
    for (int i = 0; i < t; ++i) {
        shuffleAndPrint(makeCase());
    }

    return 0;
}
