#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int n;
int totalSquares;
int stones;
vector<int> removed;

struct Claim {
    bool possible;
};

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }
    char* end = nullptr;
    long parsed = strtol(token.c_str(), &end, 10);
    if (*end != '\0' || parsed < 1 || parsed > totalSquares) {
        return false;
    }
    value = static_cast<int>(parsed);
    return true;
}

void validateSquare(InStream& stream, int square, const char* name) {
    if (square < 1 || square > totalSquares) {
        stream.quitf(_wa, "%s=%d is outside [1,%d]", name, square, totalSquares);
    }
    if (removed[square]) {
        stream.quitf(_wa, "%s=%d is one of the removed squares", name, square);
    }
}

bool adjacent(int a, int b) {
    int ar = (a - 1) / n;
    int ac = (a - 1) % n;
    int br = (b - 1) / n;
    int bc = (b - 1) % n;
    return abs(ar - br) + abs(ac - bc) == 1;
}

Claim readClaim(InStream& stream) {
    if (stream.seekEof()) {
        stream.quitf(_wa, "missing output");
    }

    string firstToken = stream.readWord();
    if (firstToken == "NIE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NIE");
        }
        return {false};
    }

    vector<int> covered(totalSquares + 1, 0);
    int firstSquare = 0;
    if (!parseIntToken(firstToken, firstSquare)) {
        stream.quitf(_wa, "expected NIE or square number, found '%s'", firstToken.c_str());
    }

    for (int i = 0; i < stones; ++i) {
        int a = firstSquare;
        if (i > 0) {
            a = stream.readInt(1, totalSquares, format("stone[%d].first", i + 1).c_str());
        }
        int b = stream.readInt(1, totalSquares, format("stone[%d].second", i + 1).c_str());

        validateSquare(stream, a, "stone square");
        validateSquare(stream, b, "stone square");
        if (!adjacent(a, b)) {
            stream.quitf(_wa, "stone %d covers non-adjacent squares %d and %d", i + 1, a, b);
        }
        if (covered[a]) {
            stream.quitf(_wa, "square %d is covered more than once", a);
        }
        if (covered[b]) {
            stream.quitf(_wa, "square %d is covered more than once", b);
        }
        covered[a] = covered[b] = 1;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d stones", stones);
    }

    for (int square = 1; square <= totalSquares; ++square) {
        if (!removed[square] && !covered[square]) {
            stream.quitf(_wa, "square %d is not covered", square);
        }
        if (removed[square] && covered[square]) {
            stream.quitf(_wa, "removed square %d is covered", square);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    totalSquares = n * n;
    stones = (totalSquares - 3) / 2;
    removed.assign(totalSquares + 1, 0);
    for (int i = 0; i < 3; ++i) {
        int square = inf.readInt();
        removed[square] = 1;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible && !participant.possible) {
        quitf(_ok, "both outputs claim no tiling");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "participant claims no tiling but jury provides a valid tiling");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provides a valid tiling while jury claims no tiling");
    }

    quitf(_ok, "valid tiling with %d stones", stones);
}
