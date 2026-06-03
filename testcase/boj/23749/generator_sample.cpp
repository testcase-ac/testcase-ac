#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 5);
    int mode = rnd.next(5);

    vector<string> cards;
    cards.reserve(2 * n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            cards.push_back("O");
            cards.push_back("X");
        }
        shuffle(cards.begin(), cards.end());
    } else if (mode == 1) {
        bool startO = rnd.next(2) == 0;
        for (int i = 0; i < n; ++i) {
            cards.push_back(startO ? "O" : "X");
            cards.push_back(startO ? "X" : "O");
        }
    } else if (mode == 2) {
        bool oFirst = rnd.next(2) == 0;
        for (int i = 0; i < n; ++i) {
            cards.push_back(oFirst ? "O" : "X");
        }
        for (int i = 0; i < n; ++i) {
            cards.push_back(oFirst ? "X" : "O");
        }
    } else if (mode == 3) {
        int sameEach = rnd.next(0, n / 2);
        int ox = n - 2 * sameEach;

        for (int i = 0; i < sameEach; ++i) {
            cards.push_back("O");
            cards.push_back("O");
        }
        for (int i = 0; i < sameEach; ++i) {
            cards.push_back("X");
            cards.push_back("X");
        }
        for (int i = 0; i < ox; ++i) {
            if (rnd.next(2) == 0) {
                cards.push_back("O");
                cards.push_back("X");
            } else {
                cards.push_back("X");
                cards.push_back("O");
            }
        }
        shuffle(cards.begin(), cards.end());
    } else {
        int prefixX = rnd.next(0, n);
        for (int i = 0; i < prefixX; ++i) {
            cards.push_back("X");
        }
        for (int i = 0; i < n; ++i) {
            cards.push_back("O");
        }
        for (int i = prefixX; i < n; ++i) {
            cards.push_back("X");
        }
    }

    println(n);
    println(cards);
}
