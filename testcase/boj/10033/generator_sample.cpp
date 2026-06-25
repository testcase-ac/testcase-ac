#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAX_X = 1000000000;

vector<int> makeClusteredPositions(int n) {
    vector<int> positions;
    int x = rnd.next(0, 30);
    for (int i = 0; i < n; ++i) {
        positions.push_back(x);
        x += rnd.next(1, 8);
    }
    return positions;
}

vector<int> makeWidePositions(int n) {
    vector<int> positions;
    int start = rnd.next(0, 1000);
    int step = max(1, (MAX_X - start) / max(1, n));
    for (int i = 0; i < n; ++i) {
        int jitter = rnd.next(0, max(0, min(1000, step - 1)));
        positions.push_back(start + i * step + jitter);
    }
    return positions;
}

string colorForMode(int mode, int i, int n, int oneWhiteIndex) {
    if (mode == 0) return i == oneWhiteIndex ? "W" : "S";
    if (mode == 1) return "W";
    if (mode == 2) return i % 2 == 0 ? "W" : "S";
    if (mode == 3) return i < n / 2 ? "W" : "S";
    if (mode == 4) return rnd.next(0, 99) < 70 ? "W" : "S";
    return rnd.next(0, 1) == 0 ? "W" : "S";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 14);
    } else if (mode == 5) {
        n = rnd.next(30, 120);
    } else {
        n = rnd.next(2, 24);
    }

    vector<int> positions;
    if (mode == 4 || mode == 5) {
        positions = makeWidePositions(n);
    } else {
        positions = makeClusteredPositions(n);
    }

    vector<pair<int, string>> cows;
    bool hasWhite = false;
    int oneWhiteIndex = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        string color = colorForMode(mode, i, n, oneWhiteIndex);
        hasWhite = hasWhite || color == "W";
        cows.push_back({positions[i], color});
    }
    if (!hasWhite) cows[rnd.next(0, n - 1)].second = "W";

    if (mode == 3 && rnd.next(0, 1) == 0) {
        reverse(cows.begin(), cows.end());
    } else {
        shuffle(cows.begin(), cows.end());
    }

    println(n);
    for (const auto& cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
