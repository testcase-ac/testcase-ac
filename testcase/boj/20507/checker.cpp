#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> initialLeft;

struct Claim {
    int moves;
};

int handIndex(const string& token, InStream& stream, int moveIndex) {
    if (token == "L") return 0;
    if (token == "D") return 1;
    stream.quitf(_wa, "invalid hand '%s' in move %d", token.c_str(), moveIndex);
}

int shelfIndex(const string& token, InStream& stream, int moveIndex) {
    if (token == "L") return 0;
    if (token == "D") return 1;
    stream.quitf(_wa, "invalid shelf '%s' in move %d", token.c_str(), moveIndex);
}

Claim readClaim(InStream& stream) {
    int k = stream.readInt(0, 100000, "k");

    vector<vector<int>> shelf(2);
    shelf[0] = initialLeft;
    vector<int> hand(2, -1);

    for (int i = 1; i <= k; ++i) {
        string instruction = stream.readWord("[A-Z]+", format("instruction[%d]", i).c_str());
        int h = handIndex(stream.readWord("[LD]", format("hand[%d]", i).c_str()), stream, i);
        int s = shelfIndex(stream.readWord("[LD]", format("shelf[%d]", i).c_str()), stream, i);

        if (instruction == "UZMI") {
            if (hand[h] != -1) {
                stream.quitf(_wa, "hand %s is not empty before move %d", h == 0 ? "L" : "D", i);
            }
            if (shelf[s].empty()) {
                stream.quitf(_wa, "shelf %s is empty before move %d", s == 0 ? "L" : "D", i);
            }
            hand[h] = shelf[s].front();
            shelf[s].erase(shelf[s].begin());
        } else if (instruction == "STAVI") {
            if (hand[h] == -1) {
                stream.quitf(_wa, "hand %s is empty before move %d", h == 0 ? "L" : "D", i);
            }
            shelf[s].insert(shelf[s].begin(), hand[h]);
            hand[h] = -1;
        } else {
            stream.quitf(_wa, "invalid instruction '%s' in move %d", instruction.c_str(), i);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after move list");
    }

    if (hand[0] != -1 || hand[1] != -1) {
        stream.quitf(_wa, "a hand is still holding a book after all moves");
    }
    if (!shelf[1].empty()) {
        stream.quitf(_wa, "right shelf contains %d books after all moves", int(shelf[1].size()));
    }
    if (int(shelf[0].size()) != n) {
        stream.quitf(_wa, "left shelf contains %d books instead of %d", int(shelf[0].size()), n);
    }
    if (!is_sorted(shelf[0].begin(), shelf[0].end())) {
        stream.quitf(_wa, "left shelf is not sorted from thinnest to thickest");
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");
    initialLeft.resize(n);
    for (int i = 0; i < n; ++i) {
        initialLeft[i] = inf.readInt(1, 1000, format("d[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid sequence with %d moves; jury used %d moves", participant.moves, jury.moves);
}
