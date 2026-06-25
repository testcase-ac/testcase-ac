#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        if (n % 2 == 1) ++n;
    } else if (mode == 2) {
        n = rnd.next(1, 11);
        if (n % 2 == 0) ++n;
    } else {
        n = rnd.next(2, 20);
    }

    vector<string> cards;
    if (mode == 0) {
        cards.assign(n, "O");
        cards.insert(cards.end(), n, "X");
    } else if (mode == 1) {
        cards.assign(n, "X");
        cards.insert(cards.end(), n, "O");
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            cards.push_back("O");
            cards.push_back("X");
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            cards.push_back("X");
            cards.push_back("O");
        }
    } else if (mode == 4) {
        int frontO = rnd.next(0, n);
        cards.insert(cards.end(), frontO, "O");
        cards.insert(cards.end(), n - frontO, "X");
        cards.insert(cards.end(), n - frontO, "O");
        cards.insert(cards.end(), frontO, "X");
    } else if (mode == 5) {
        int frontX = rnd.next(0, n);
        cards.insert(cards.end(), frontX, "X");
        cards.insert(cards.end(), n - frontX, "O");
        cards.insert(cards.end(), n - frontX, "X");
        cards.insert(cards.end(), frontX, "O");
    } else {
        cards.assign(n, "O");
        cards.insert(cards.end(), n, "X");
        shuffle(cards.begin(), cards.end());
    }

    println(n);
    println(cards);

    return 0;
}
