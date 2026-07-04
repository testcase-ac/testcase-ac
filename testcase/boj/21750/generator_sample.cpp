#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

string squareName(pair<int, int> sq) {
    string s;
    s += char('a' + sq.first);
    s += char('1' + sq.second);
    return s;
}

bool sameSquare(pair<int, int> a, pair<int, int> b) {
    return a == b;
}

pair<int, int> randomSquare() {
    return {rnd.next(0, 7), rnd.next(0, 7)};
}

pair<int, int> randomDifferentFrom(pair<int, int> forbidden) {
    pair<int, int> sq = randomSquare();
    while (sameSquare(sq, forbidden)) {
        sq = randomSquare();
    }
    return sq;
}

pair<int, int> randomNear(pair<int, int> base) {
    vector<pair<int, int>> candidates;
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            int x = base.first + dx;
            int y = base.second + dy;
            if (0 <= x && x < 8 && 0 <= y && y < 8 && (dx != 0 || dy != 0)) {
                candidates.push_back({x, y});
            }
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> corners = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};
    pair<int, int> whiteStart;
    pair<int, int> blackStart;
    pair<int, int> whiteTarget;
    pair<int, int> blackTarget;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        whiteStart = rnd.any(corners);
        blackStart = randomDifferentFrom(whiteStart);
        whiteTarget = randomDifferentFrom(blackStart);
        blackTarget = randomDifferentFrom(whiteTarget);
    } else if (mode == 1) {
        whiteStart = randomSquare();
        blackStart = randomDifferentFrom(whiteStart);
        whiteTarget = blackStart;
        blackTarget = whiteStart;
    } else if (mode == 2) {
        whiteStart = randomSquare();
        blackStart = randomDifferentFrom(whiteStart);
        whiteTarget = whiteStart;
        blackTarget = randomDifferentFrom(whiteTarget);
    } else if (mode == 3) {
        whiteStart = randomSquare();
        blackStart = randomNear(whiteStart);
        whiteTarget = randomNear(blackStart);
        blackTarget = randomNear(whiteTarget);
    } else {
        whiteStart = randomSquare();
        blackStart = randomDifferentFrom(whiteStart);
        whiteTarget = randomSquare();
        blackTarget = randomDifferentFrom(whiteTarget);
    }

    println(squareName(whiteStart), squareName(blackStart), squareName(whiteTarget),
            squareName(blackTarget));

    return 0;
}
